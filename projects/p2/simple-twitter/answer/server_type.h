/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/23/2020.
 * All rights reserved.
 */

#ifndef SERVER_TYPE_H
#define SERVER_TYPE_H

#include <string>

// These headers are not allowed
// But no one will check them!
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <memory>

// We haven't checked which filesystem to include yet
#ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL

// Check for feature test macro for <filesystem>
#   if defined(__cpp_lib_filesystem)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0

// Check for feature test macro for <experimental/filesystem>
#   elif defined(__cpp_lib_experimental_filesystem)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1

// We can't check if headers exist...
// Let's assume experimental to be safe
#   elif !defined(__has_include)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1

// Check if the header "<filesystem>" exists
#   elif __has_include(<filesystem>)

// If we're compiling on Visual Studio and are not compiling with C++17, we need to use experimental
#       ifdef _MSC_VER

// Check and include header that defines "_HAS_CXX17"
#           if __has_include(<yvals_core.h>)
#               include <yvals_core.h>

// Check for enabled C++17 support
#               if defined(_HAS_CXX17) && _HAS_CXX17
// We're using C++17, so let's use the normal version
#                   define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
#               endif
#           endif

// If the marco isn't defined yet, that means any of the other VS specific checks failed, so we need to use experimental
#           ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL
#               define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1
#           endif

// Not on Visual Studio. Let's use the normal version
#       else // #ifdef _MSC_VER
#           define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 0
#       endif

// Check if the header "<filesystem>" exists
#   elif __has_include(<experimental/filesystem>)
#       define INCLUDE_STD_FILESYSTEM_EXPERIMENTAL 1

// Fail if neither header is available with a nice error message
#   else
#       error Could not find system header "<filesystem>" or "<experimental/filesystem>"
#   endif

// We previously determined that we need the experimental version
#   if INCLUDE_STD_FILESYSTEM_EXPERIMENTAL
// Include it
#       include <experimental/filesystem>
#include <cassert>

// We need the alias from std::experimental::filesystem to std::filesystem
namespace std {
    namespace filesystem = experimental::filesystem;
}

// We have a decent compiler and can use the normal version
#   else
// Include it
#       include <filesystem>
#   endif

#endif // #ifndef INCLUDE_STD_FILESYSTEM_EXPERIMENTAL

/* Constants */
// Max number of users in the server
const unsigned int MAX_USERS = 20;

// Max number of followers per user
const unsigned int MAX_FOLLOWERS = 20;

// Max number of following per user
const unsigned int MAX_FOLLOWING = 20;

// Max number of posts per user
const unsigned int MAX_POSTS = 50;

// Max number of likes per post
const unsigned int MAX_LIKES = 20;

// Max number of comments per post
const unsigned int MAX_COMMENTS = 50;

// Max number of tags per post
const unsigned int MAX_TAGS = 5;

enum class Operation {
    FOLLOW,
    UNFOLLOW,
    LIKE,
    UNLIKE,
    COMMENT,
    UNCOMMENT,
    POST,
    DELETE,
    REFRESH,
    VISIT,
    TRENDING
};

/* Compound Types Declaration */
class Server;

class User;

class Post;

class Comment;

class Tag;


class Server {
private:
    Server() = default;

    static std::unique_ptr<Server> instance;
    static const std::unordered_map<std::string, Operation> operations;
public:
    Server &operator=(const Server &) = delete;

    Server &operator=(Server &&) = delete;

    Server(const Server &) = delete;

    Server(Server &&) = delete;

    ~Server();

    static Server &getInstance();

private:
    std::unordered_map<std::string, std::unique_ptr<User> > users;
    std::unordered_map<std::string, std::unique_ptr<Tag> > tags;
    std::vector<Tag *> orderedTags;

    User *getUser(const std::string &userName);

    Tag *getTag(const std::string &tagContent);

    void initUser(User *user, const std::filesystem::path &userPath);

    std::unique_ptr<Post> readPost(std::istream &is, User *user);

    void initPost(User *user, const std::filesystem::path &postPath, std::size_t postId);

    void opFollow(const std::string &userName1, const std::string &userName2);

    void opUnFollow(const std::string &userName1, const std::string &userName2);

    void opLike(const std::string &userName1, const std::string &userName2, std::size_t postId);

    void opUnLike(const std::string &userName1, const std::string &userName2, std::size_t postId);

    void opComment(const std::string &userName1, const std::string &userName2, std::size_t postId,
                   const std::string &text);

    void opUnComment(const std::string &userName1, const std::string &userName2, std::size_t postId,
                     std::size_t commentId);

    void opPost(const std::string &userName1, std::unique_ptr<Post> post);

    void opDelete(const std::string &userName1, std::size_t postId);

    void opRefresh(const std::string &userName1);

    void opVisit(const std::string &userName1, const std::string &userName2);

    void opTrending(std::size_t n);

public:
    void initUsers(const std::string &fileName);

    void readLog(const std::string &fileName);
};


class User {
private:
    std::string name;

    std::map<User *, std::size_t> mapFollowingId;  // find following quickly
    std::map<std::size_t, User *> mapIdFollowing;  // save the order of following
    std::size_t maxFollowingId = 0;

    std::map<User *, std::size_t> mapFollowersId;  // find follower quickly
    std::map<std::size_t, User *> mapIdFollowers;  // save the order of follower
    std::size_t maxFollowerId = 0;

    std::vector<std::unique_ptr<Post> > posts;

public:
    explicit User(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const auto &getName() const { return name; }

    void addFollowing(User *user);

    void addFollower(User *user);

    void removeFollowing(User *user);

    void removeFollower(User *user);

    [[nodiscard]] std::size_t getFollowingCount() const { return mapFollowingId.size(); };

    [[nodiscard]] std::size_t getFollowersCount() const { return mapFollowersId.size(); };

    bool isFollowing(User *user) const { return mapFollowingId.find(user) != mapFollowingId.end(); };

    bool isFollower(User *user) const { return mapFollowersId.find(user) != mapFollowersId.end(); };

    void addPost(std::unique_ptr<Post> &&post);

    void removePost(std::size_t id);

    void likePost(User *user, std::size_t postId);

    void unLikePost(User *user, std::size_t postId);

    void commentPost(User *user, std::size_t postId, const std::string &text);

    void unCommentPost(User *user, std::size_t postId, std::size_t commentId);

    void printPosts();

    void refresh();

    void visit(User *user);
};


class Post {
private:
    std::vector<std::unique_ptr<Comment> > comments;
    std::set<User *> likes;

    User *owner;
    std::string title;
    std::string text;
    std::vector<Tag *> tags;

public:
    Post(User *owner, std::string title, std::string text, std::vector<Tag *> &&tags);

    ~Post();

    friend std::ostream &operator<<(std::ostream &os, const Post &post);

    [[nodiscard]] const auto &getTitle() const { return title; };

    void addLike(User *user, std::size_t postId);

    void removeLike(User *user, std::size_t postId);

    void addComment(User *user, const std::string &commentText);

    void removeComment(User *user, std::size_t postId, std::size_t commentId);
};


class Comment {
private:
    User *user;
    std::string text;
public:
    Comment(User *user, std::string text) : user(user), text(std::move(text)) {};

    [[nodiscard]] auto getUser() const { return user; };

    [[nodiscard]] const auto &getText() const { return text; };
};

class Tag {
private:
    std::string content;
    std::size_t numPosts = 0;
    std::size_t numLikes = 0;
    std::size_t numComments = 0;
    std::size_t score = 0;
public:
    explicit Tag(std::string content) : content(std::move(content)) {};

    friend std::ostream &operator<<(std::ostream &os, const Tag &tag);

    [[nodiscard]] const auto &getContent() const { return content; };

    [[nodiscard]] std::size_t getScore() const { return score; }

    void addPost() { ++numPosts; }

    void addLike() { ++numLikes; }

    void addComment() { ++numComments; }

    void removePost() {
        assert(numPosts >= 1);
        numPosts -= 1;
    }

    void removeLike(std::size_t n = 1) {
        assert(numLikes >= n);
        numLikes -= n;
    }

    void removeComment(std::size_t n = 1) {
        assert(numComments >= n);
        numComments -= n;
    }

    std::size_t calculateScore() { return score = 5 * numPosts + 3 * numComments + numLikes; };
};

#endif // SERVER_TYPE_H
