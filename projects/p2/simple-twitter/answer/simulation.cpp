/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/23/2020.
 * All rights reserved.
 */

#include "server_type.h"
#include "simulation.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <unordered_set>

std::unique_ptr<Server> Server::instance = nullptr;

const std::unordered_map<std::string, Operation> Server::operations = {
        {"follow",    Operation::FOLLOW},
        {"unfollow",  Operation::UNFOLLOW},
        {"like",      Operation::LIKE},
        {"unlike",    Operation::UNLIKE},
        {"comment",   Operation::COMMENT},
        {"uncomment", Operation::UNCOMMENT},
        {"post",      Operation::POST},
        {"delete",    Operation::DELETE},
        {"refresh",   Operation::REFRESH},
        {"visit",     Operation::VISIT},
        {"trending",  Operation::TRENDING},
};

Server::~Server() {
    // we must clear users first because there exists Tag references in User
    users.clear();
    tags.clear();
}

Server &Server::getInstance() {
    if (instance == nullptr) {
        instance = std::unique_ptr<Server>(new Server);
    }
    return *instance;
}

User *Server::getUser(const std::string &userName) {
    auto it = users.find(userName);
    if (it != users.end()) {
        return it->second.get();
    }
    throw UserNotFoundException(userName);
}

Tag *Server::getTag(const std::string &tagContent) {
    auto it = tags.find(tagContent);
    if (it == tags.end()) {
        auto tag = std::make_unique<Tag>(tagContent);
        orderedTags.emplace_back(tag.get());
        it = tags.emplace_hint(it, tagContent, std::move(tag));
    }
    return it->second.get();
}

void Server::initUser(User *user, const std::filesystem::path &userPath) {
    auto userInfoPath = userPath / "user_info";
    std::fstream fin(userInfoPath.string());
    if (!fin.is_open()) {
        throw FileMissingException(userInfoPath.string());
    }

    std::string line;

    std::getline(fin, line);
    std::size_t numPosts = std::strtoul(line.c_str(), nullptr, 10);
    if (numPosts > MAX_POSTS) {
        throw TooManyPostsException(user->getName());
    }
    for (unsigned int i = 0; i < numPosts; i++) {
        initPost(user, userPath, i);
    }

    std::getline(fin, line);
    std::size_t numFollowing = std::strtoul(line.c_str(), nullptr, 10);
    if (numFollowing > MAX_FOLLOWING) {
        throw TooManyFollowingsException(user->getName());
    }
    for (unsigned int i = 0; i < numFollowing; i++) {
        std::getline(fin, line);
        auto user2 = getUser(line);
        user->addFollowing(user2);
    }

    std::getline(fin, line);
    std::size_t numFollowers = std::strtoul(line.c_str(), nullptr, 10);
    if (numFollowers > MAX_FOLLOWERS) {
        throw TooManyFollowersException(user->getName());
    }
    for (unsigned int i = 0; i < numFollowers; i++) {
        std::getline(fin, line);
        auto user2 = getUser(line);
        user->addFollower(user2);
    }

    fin.close();
}

std::unique_ptr<Post> Server::readPost(std::istream &is, User *user) {
    std::string text, title;
    std::vector<Tag *> postTags;
    std::unordered_set<Tag *> set;

    std::getline(is, title);
    while (std::getline(is, text)) {
        if (text.length() >= 2 && text.front() == '#' && text.back() == '#') {
            auto tagContent = text.substr(1, text.length() - 2);
            auto tag = getTag(tagContent);
            auto it = set.find(tag);
            if (it == set.end()) {
                set.emplace(tag);
                postTags.emplace_back(tag);
            }
        } else {
            break;
        }
    }

    if (postTags.size() > MAX_TAGS) {
        throw TooManyTagsException(title);
    }

    return std::make_unique<Post>(user, title, text, std::move(postTags));
}

void Server::initPost(User *user, const std::filesystem::path &userPath, std::size_t postId) {
    auto postPath = userPath / "posts" / std::to_string(postId + 1);
    std::fstream fin(postPath.string());
    if (!fin.is_open()) {
        throw FileMissingException(postPath.string());
    }

    std::string userName;
    auto post = readPost(fin, user);

    std::string line;
    std::getline(fin, line);
    std::size_t numLikes = std::strtoul(line.c_str(), nullptr, 10);
    if (numLikes > MAX_LIKES) {
        throw TooManyLikesException(post->getTitle());
    }
    for (unsigned int i = 0; i < numLikes; i++) {
        std::getline(fin, userName);
        auto user2 = getUser(userName);
        post->addLike(user2, postId);
    }

    std::getline(fin, line);
    std::size_t numComments = std::strtoul(line.c_str(), nullptr, 10);
    if (numComments > MAX_COMMENTS) {
        throw TooManyCommentsException(post->getTitle());
    }
    for (unsigned int i = 0; i < numComments; i++) {
        std::getline(fin, userName);
        auto user2 = getUser(userName);
        std::getline(fin, line);
        post->addComment(user2, line);
    }

    user->addPost(std::move(post));

    fin.close();
}


void Server::initUsers(const std::string &fileName) {
    std::fstream fin(fileName);
    if (!fin.is_open()) {
        throw FileMissingException(fileName);
    }
    std::string usersDirectory;
    std::getline(fin, usersDirectory);
    std::filesystem::path usersPath(usersDirectory);

    std::string userName;
    while (std::getline(fin, userName)) {
        if (userName.empty()) continue;
        auto user = std::make_unique<User>(userName);
        users.emplace(userName, std::move(user));
    }
    if (users.size() > MAX_USERS) {
        throw TooManyUsersException();
    }
    for (auto &p : users) {
        const auto &name = p.second->getName();
        auto userPath = usersPath / name;
        initUser(p.second.get(), userPath);
    }
    fin.close();
}


void Server::readLog(const std::string &fileName) {
    std::fstream fin(fileName);
    if (!fin.is_open()) {
        throw FileMissingException(fileName);
    }
    std::string line;
    std::istringstream iss;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        iss.clear();
        iss.str(line);
        std::string u1, op, u2, text;
        std::size_t postId, commentId;
        iss >> u1;

        if (u1 == "trending") {
            // test whether "trending" is username
            std::string temp;
            iss >> temp;
            if (operations.find(temp) == operations.end()) {
                // "trending" is not username, reset the iss
                iss.clear();
                iss.str(line);
                iss >> op;
            } else {
                // "trending" is username, so temp is op
                op = std::move(temp);
            }
        } else {
            iss >> op;
        }


        try {
            auto it = operations.find(op);
            if (it == operations.end()) {
                throw InvalidOperationException(op);
            }
            std::cout << ">> " << op << std::endl;
            auto operation = it->second;
            switch (operation) {
                case Operation::FOLLOW:
                    iss >> u2;
                    opFollow(u1, u2);
                    break;
                case Operation::UNFOLLOW:
                    iss >> u2;
                    opUnFollow(u1, u2);
                    break;
                case Operation::LIKE:
                    iss >> u2 >> postId;
                    opLike(u1, u2, --postId);
                    break;
                case Operation::UNLIKE:
                    iss >> u2 >> postId;
                    opUnLike(u1, u2, --postId);
                    break;
                case Operation::COMMENT:
                    iss >> u2 >> postId;
                    std::getline(fin, text);
                    opComment(u1, u2, --postId, text);
                    break;
                case Operation::UNCOMMENT:
                    iss >> u2 >> postId >> commentId;
                    opUnComment(u1, u2, --postId, --commentId);
                    break;
                case Operation::POST:
                    opPost(u1, readPost(fin, getUser(u1)));
                    break;
                case Operation::DELETE:
                    iss >> postId;
                    opDelete(u1, --postId);
                    break;
                case Operation::REFRESH:
                    opRefresh(u1);
                    break;
                case Operation::VISIT:
                    iss >> u2;
                    opVisit(u1, u2);
                    break;
                case Operation::TRENDING:
                    std::size_t n;
                    iss >> n;
                    opTrending(n);
                    break;
            }
        } catch (SimpleTwitterException &e) {
            std::cout << e.what() << std::endl;
        }
    }
    fin.close();
}


void Server::opFollow(const std::string &userName1, const std::string &userName2) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);

    if (u1 == u2) {
        throw FollowException(userName1, userName2);
    }
    if (u1->getFollowingCount() >= MAX_FOLLOWING) {
        throw TooManyFollowingsException(userName1);
    }
    if (u2->getFollowersCount() >= MAX_FOLLOWERS) {
        throw TooManyFollowersException(userName2);
    }
    if (u1->isFollowing(u2) || u2->isFollower(u1)) {
        throw FollowException(userName1, userName2);
    }

    u1->addFollowing(u2);
    u2->addFollower(u1);
}

void Server::opUnFollow(const std::string &userName1, const std::string &userName2) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);

    if (!u1->isFollowing(u2) || !u2->isFollower(u1)) {
        throw UnFollowException(userName1, userName2);
    }

    u1->removeFollowing(u2);
    u2->removeFollower(u1);
}

void Server::opLike(const std::string &userName1, const std::string &userName2, std::size_t postId) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);
    u1->likePost(u2, postId);
}

void Server::opUnLike(const std::string &userName1, const std::string &userName2, std::size_t postId) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);
    u1->unLikePost(u2, postId);
}

void Server::opComment(const std::string &userName1, const std::string &userName2, std::size_t postId,
                       const std::string &text) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);
    u1->commentPost(u2, postId, text);
}

void Server::opUnComment(const std::string &userName1, const std::string &userName2, std::size_t postId,
                         std::size_t commentId) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);
    u1->unCommentPost(u2, postId, commentId);
}

void Server::opPost(const std::string &userName1, std::unique_ptr<Post> post) {
    auto u1 = getUser(userName1);
    u1->addPost(std::move(post));
}

void Server::opDelete(const std::string &userName1, std::size_t postId) {
    auto u1 = getUser(userName1);
    u1->removePost(postId);
}

void Server::opRefresh(const std::string &userName1) {
    auto u1 = getUser(userName1);
    u1->refresh();
}

void Server::opVisit(const std::string &userName1, const std::string &userName2) {
    auto u1 = getUser(userName1);
    auto u2 = getUser(userName2);
    u1->visit(u2);
}

void Server::opTrending(std::size_t n) {
    std::sort(orderedTags.begin(), orderedTags.end(), [](const Tag *a, const Tag *b) {
        if (a->getScore() != b->getScore()) return a->getScore() > b->getScore();
        return a->getContent() < b->getContent();
    });
    for (unsigned int i = 0; i < std::min(n, orderedTags.size()); i++) {
        if (orderedTags[i]->getScore() == 0) break;
        std::cout << i + 1 << " " << *orderedTags[i] << std::endl;
    }
}

void User::addFollowing(User *user) {
    auto it = mapFollowingId.find(user);
    if (it == mapFollowingId.end()) {
        auto followingId = ++maxFollowingId;
        mapFollowingId.emplace(user, followingId);
        mapIdFollowing.emplace(followingId, user);
    }
}

void User::addFollower(User *user) {
    auto it = mapFollowersId.find(user);
    if (it == mapFollowersId.end()) {
        auto followerId = ++maxFollowerId;
        mapFollowersId.emplace(user, followerId);
        mapIdFollowers.emplace(followerId, user);
    }
}

void User::removeFollowing(User *user) {
    auto it = mapFollowingId.find(user);
    if (it != mapFollowingId.end()) {
        auto followingId = it->second;
        mapFollowingId.erase(it);
        mapIdFollowing.erase(followingId);
    }
}

void User::removeFollower(User *user) {
    auto it = mapFollowersId.find(user);
    if (it != mapFollowersId.end()) {
        auto followerId = it->second;
        mapFollowersId.erase(it);
        mapIdFollowers.erase(followerId);
    }
}

void User::addPost(std::unique_ptr<Post> &&post) {
    if (posts.size() >= MAX_POSTS) {
        throw TooManyPostsException(name);
    }
    posts.emplace_back(std::move(post));
}

void User::removePost(std::size_t id) {
    if (id >= posts.size()) {
        throw DeletePostException(name, id);
    }
    auto it = posts.begin() + id;
    posts.erase(it);
}

void User::likePost(User *user, std::size_t postId) {
    if (postId >= user->posts.size()) {
        throw LikeException(name, user->getName(), postId, SimpleTwitterException::NOT_EXIST);
    }
    auto it = user->posts.begin() + postId;
    (*it)->addLike(this, postId);
}

void User::unLikePost(User *user, std::size_t postId) {
    if (postId >= user->posts.size()) {
        throw UnLikeException(name, user->getName(), postId, SimpleTwitterException::NOT_EXIST);
    }
    auto it = user->posts.begin() + postId;
    (*it)->removeLike(this, postId);
}

void User::commentPost(User *user, std::size_t postId, const std::string &text) {
    if (postId >= user->posts.size()) {
        throw CommentException(name, user->getName(), postId);
    }
    auto it = user->posts.begin() + postId;
    (*it)->addComment(this, text);
}

void User::unCommentPost(User *user, std::size_t postId, std::size_t commentId) {
    if (postId >= user->posts.size()) {
        throw UnCommentException(name, user->getName(), postId, commentId, SimpleTwitterException::NOT_EXIST);
    }
    auto it = user->posts.begin() + postId;
    (*it)->removeComment(this, postId, commentId);
}

void User::printPosts() {
    for (const auto &post : posts) {
        std::cout << *post;
    }
}

void User::refresh() {
    printPosts();
    for (auto p : mapIdFollowing) {
        p.second->printPosts();
    }
}

void User::visit(User *user) {
    std::cout << user->name << std::endl;
    if (this != user) {
        if (this->isFollowing(user)) {
            if (user->isFollowing(this)) {
                std::cout << "friend" << std::endl;
            } else {
                std::cout << "following" << std::endl;
            }
        } else {
            std::cout << "stranger" << std::endl;
        }
    } else {
        std::cout << std::endl;
    }
    std::cout << "Followers: " << user->mapFollowersId.size() << std::endl;
    std::cout << "Following: " << user->mapFollowingId.size() << std::endl;
}

Post::Post(User *owner, std::string title, std::string text, std::vector<Tag *> &&tags) :
        owner(owner), title(std::move(title)), text(std::move(text)), tags(std::move(tags)) {
    for (auto tag : this->tags) {
        tag->addPost();
        tag->calculateScore();
    }
}

Post::~Post() {
    for (auto tag : this->tags) {
        tag->removePost();
        tag->removeLike(likes.size());
        tag->removeComment(comments.size());
        tag->calculateScore();
    }
}

std::ostream &operator<<(std::ostream &os, const Post &post) {
    os << post.owner->getName() << std::endl;
    os << post.title << std::endl;
    os << post.text << std::endl;
    os << "Tags: ";
    for (auto tag : post.tags) {
        os << tag->getContent() << " ";
    }
    os << std::endl << "Likes: " << post.likes.size() << std::endl;
    if (!post.comments.empty()) {
        os << "Comments:" << std::endl;
        for (auto &comment : post.comments) {
            os << comment->getUser()->getName() << ": "
               << comment->getText() << std::endl;
        }
    }
    os << "- - - - - - - - - - - - - - -" << std::endl;
    return os;
}


void Post::addLike(User *user, std::size_t postId) {
    auto it = likes.find(user);
    if (it != likes.end()) {
        throw LikeException(user->getName(), owner->getName(), postId, SimpleTwitterException::ALREADY_DONE);
    }
    if (likes.size() >= MAX_LIKES) {
        throw TooManyLikesException(title);
    }
    likes.emplace_hint(it, user);
    for (auto tag: tags) {
        tag->addLike();
        tag->calculateScore();
    }
}

void Post::removeLike(User *user, std::size_t postId) {
    auto it = likes.find(user);
    if (it == likes.end()) {
        throw UnLikeException(user->getName(), owner->getName(), postId, SimpleTwitterException::NOT_DONE);
    }
    likes.erase(it);
    for (auto tag: tags) {
        tag->removeLike();
        tag->calculateScore();
    }
}

void Post::addComment(User *user, const std::string &commentText) {
    if (comments.size() >= MAX_COMMENTS) {
        throw TooManyCommentsException(title);
    }
    comments.emplace_back(std::make_unique<Comment>(user, commentText));
    for (auto tag: tags) {
        tag->addComment();
        tag->calculateScore();
    }
}

void Post::removeComment(User *user, std::size_t postId, std::size_t commentId) {
    if (commentId >= comments.size()) {
        throw UnCommentException(user->getName(), owner->getName(), postId, commentId,
                                 SimpleTwitterException::NOT_DONE);
    }
    auto it = comments.begin() + commentId;
    if (user != (*it)->getUser()) {
        throw UnCommentException(user->getName(), owner->getName(), postId, commentId,
                                 SimpleTwitterException::NOT_OWNER);
    }
    comments.erase(it);
    for (auto tag: tags) {
        tag->removeComment();
        tag->calculateScore();
    }
}


std::ostream &operator<<(std::ostream &os, const Tag &tag) {
    return os << tag.content << ": " << tag.score;
}
