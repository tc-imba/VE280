//
// Created by liu on 8/6/2020.
//

#include "server_type.h"
#include "simulation.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cassert>

int main(int argc, char *argv[]) {
#ifdef DEBUG
    std::ofstream fout("test.out2");
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(fout.rdbuf());
#endif

    static Server_t server;

    try {
        if (argc <= 2) {
            throw Exception_t(INVALID_ARGUMENT, "");
        }

        // read username file
        string username_filename = argv[1];
        ifstream username_file(username_filename);
        if (!username_file.is_open()) {
            throw Exception_t(FILE_MISSING, username_filename);
        }
        string users_directory;
        getline(username_file, users_directory);
        string username;
        while (getline(username_file, username)) {
            if (username.empty()) continue;
            if (server.num_users >= MAX_USERS) {
                throw Exception_t(CAPACITY_OVERFLOW, "users", MAX_USERS);
            }
            server.users[server.num_users++].username = username;
        }
        username_file.close();

        // read each user's info and posts
        for (unsigned int i = 0; i < server.num_users; i++) {
            auto &user = server.users[i];
            auto user_path = users_directory + "/" + user.username;
            auto user_info_filename = user_path + "/user_info";
            ifstream user_info_file(user_info_filename);
            if (!user_info_file.is_open()) {
                throw Exception_t(FILE_MISSING, user_info_filename);
            }
            string temp;
            getline(user_info_file, temp);
            user.num_posts = strtoul(temp.c_str(), nullptr, 10);
            if (user.num_posts > MAX_POSTS) {
                throw Exception_t(CAPACITY_OVERFLOW, "posts",
                                  "posts for user " + user.username, MAX_POSTS);
            }
            getline(user_info_file, temp);
            user.num_following = strtoul(temp.c_str(), nullptr, 10);
            if (user.num_following > MAX_FOLLOWING) {
                throw Exception_t(CAPACITY_OVERFLOW, "followings",
                                  "followings for user " + user.username, MAX_FOLLOWING);
            }
            for (unsigned int j = 0; j < user.num_following; j++) {
                getline(user_info_file, temp);
                user.following[j] = find_if(server.users, server.users + server.num_users,
                                            [&](const auto &user) { return user.username == temp; });
                // this find_if is equivalent to
                // User *find(Server_t &server, const string &temp) {
                //     for (int i = 0; i < server.num_users; i++) {
                //         if (server.users[i].username == temp)
                //             return server.users + i;
                //     }
                //     return server.users + server.num_users;
                // }
            }
            getline(user_info_file, temp);
            user.num_followers = strtoul(temp.c_str(), nullptr, 10);
            if (user.num_followers > MAX_FOLLOWERS) {
                throw Exception_t(CAPACITY_OVERFLOW, "followers",
                                  "followers for user " + user.username, MAX_FOLLOWERS);
            }
            for (unsigned int j = 0; j < user.num_followers; j++) {
                getline(user_info_file, temp);
                user.followers[j] = find_if(server.users, server.users + server.num_users,
                                            [&](const auto &user) { return user.username == temp; });
            }
            user_info_file.close();
            // read posts
            for (unsigned int j = 0; j < user.num_posts; j++) {
                auto &post = user.posts[j];
                post.owner = &user;
                auto post_filename = user_path + "/posts/" + to_string(j + 1);
                ifstream post_file(post_filename);
                if (!post_file.is_open()) {
                    throw Exception_t(FILE_MISSING, post_filename);
                }
                getline(post_file, post.title);
                while (getline(post_file, post.text)) {
                    if (post.text.length() >= 2 && post.text.front() == '#' && post.text.back() == '#') {
                        auto tag_content = post.text.substr(1, post.text.length() - 2);
                        if (find(post.tags, post.tags + post.num_tags, tag_content) != post.tags + post.num_tags) {
                            // this is very similar to find_if, except we can use value comparison directly
                            // we skip tags with same value here
                            continue;
                        }
                        if (post.num_tags >= MAX_TAGS) {
                            throw Exception_t(CAPACITY_OVERFLOW, "tags",
                                              "tags for post " + post.title, MAX_TAGS);
                        }
                        post.tags[post.num_tags++] = tag_content;
                    } else {
                        break;
                    }
                }
                getline(post_file, temp);
                post.num_likes = strtoul(temp.c_str(), nullptr, 10);
                if (post.num_likes > MAX_LIKES) {
                    throw Exception_t(CAPACITY_OVERFLOW, "likes",
                                      "likes for post " + post.title, MAX_LIKES);
                }
                for (unsigned int k = 0; k < post.num_likes; k++) {
                    getline(post_file, temp);
                    post.like_users[k] = find_if(server.users, server.users + server.num_users,
                                                 [&](const auto &user) { return user.username == temp; });
                }
                getline(post_file, temp);
                post.num_comments = strtoul(temp.c_str(), nullptr, 10);
                if (post.num_comments > MAX_COMMENTS) {
                    throw Exception_t(CAPACITY_OVERFLOW, "comments",
                                      "comments for post " + post.title, MAX_COMMENTS);
                }
                for (unsigned int k = 0; k < post.num_comments; k++) {
                    getline(post_file, temp);
                    post.comments[k].user = find_if(server.users, server.users + server.num_users,
                                                    [&](const auto &user) { return user.username == temp; });
                    getline(post_file, post.comments[k].text);
                }
                post_file.close();
            }
        }

        string log_filename = argv[2];
        ifstream log_file(log_filename);
        if (!log_file.is_open()) {
            throw Exception_t(FILE_MISSING, log_filename);
        }
        string line;
        istringstream iss;
        ostringstream oss;
        while (std::getline(log_file, line)) {
            if (line.empty()) continue;
            iss.clear();
            iss.str(line);
            oss.clear();
            oss.str("");
            string u1, op, u2, text, info;
            unsigned int post_id, comment_id;
            iss >> u1;
            try {
                if (u1 == "trending") {
                    cout << ">> " << u1 << endl;
                    unsigned int n;
                    iss >> n;
                    server.num_tags = 0;
                    for (unsigned int i = 0; i < server.num_users; i++) {
                        auto &user = server.users[i];
                        for (unsigned int j = 0; j < user.num_posts; j++) {
                            auto &post = user.posts[j];
                            for (unsigned int k = 0; k < post.num_tags; k++) {
                                auto &tag_content = post.tags[k];
                                auto tag = find_if(server.tags, server.tags + server.num_tags,
                                                   [&](const auto &t) { return t.tag_content == tag_content; });
                                if (tag == server.tags + server.num_tags) {
                                    tag = server.tags + server.num_tags++;
                                    tag->tag_content = tag_content;
                                    tag->tag_score = 0;
                                }
                                tag->tag_score += 5 + 3 * post.num_comments + post.num_likes;
                            }
                        }
                    }
                    sort(server.tags, server.tags + server.num_tags, [](const auto &a, const auto &b) {
                        if (a.tag_score != b.tag_score) return a.tag_score > b.tag_score;
                        return a.tag_content < b.tag_content;
                    });
                    for (unsigned int i = 0; i < min(n, server.num_tags); i++) {
                        cout << i + 1 << " " << server.tags[i].tag_content << ": " << server.tags[i].tag_score << endl;
                    }
                    continue;
                }
                auto user1 = find_if(server.users, server.users + server.num_users,
                                     [&](const auto &user) { return user.username == u1; });
                assert(user1 != end(server.users));
                iss >> op;
                cout << ">> " << op << endl;
                if (op == "post") {
                    assert(user1->num_posts < MAX_POSTS);
                    auto &post = user1->posts[user1->num_posts++];
                    post.num_tags = post.num_likes = post.num_comments = 0;
                    post.owner = user1;
                    getline(log_file, post.title);
                    while (getline(log_file, post.text)) {
                        if (post.text.length() >= 2 && post.text.front() == '#' && post.text.back() == '#') {
                            auto tag_content = post.text.substr(1, post.text.length() - 2);
                            if (find(post.tags, post.tags + post.num_tags, tag_content) != post.tags + post.num_tags) {
                                continue;
                            }
                            assert(post.num_tags < MAX_TAGS);
                            post.tags[post.num_tags++] = tag_content;
                        } else {
                            break;
                        }
                    }
                    continue;
                }
                if (op == "delete") {
                    iss >> post_id;
                    if (--post_id >= user1->num_posts) {
                        info = "Error: " + u1 + " cannot delete post #" + to_string(post_id + 1) + "!\n";
                        info += u1 + " does not have post #" + to_string(post_id + 1) + ".";
                        throw Exception_t(INVALID_LOG, info);
                    }
                    // copy from [post_id+1, num_posts) to [post_id, num_posts-1), and also num_posts--
                    copy(user1->posts + post_id + 1, user1->posts + user1->num_posts--, user1->posts + post_id);
                    continue;
                }
                if (op == "refresh") {
                    for (unsigned int i = 0; i < user1->num_posts; i++) {
                        printPost(user1->posts[i]);
                    }
                    for (unsigned int j = 0; j < user1->num_following; j++) {
                        auto user2 = user1->following[j];
                        for (unsigned int i = 0; i < user2->num_posts; i++) {
                            printPost(user2->posts[i]);
                        }
                    }
                    continue;
                }
                iss >> u2;
                auto user2 = find_if(server.users, server.users + server.num_users,
                                     [&](const auto &user) { return user.username == u2; });
                assert(user2 != end(server.users));
                if (op == "follow" || op == "unfollow") {
                    assert(user1 != user2);
                    auto p1 = find(user1->following, user1->following + user1->num_following, user2);
                    auto p2 = find(user2->followers, user2->followers + user2->num_followers, user1);
                    if (op == "follow") {
                        assert(user1->num_following < MAX_FOLLOWING);
                        assert(user2->num_followers < MAX_FOLLOWERS);
                        assert(p1 == user1->following + user1->num_following);
                        assert(p2 == user2->followers + user2->num_followers);
                        user1->following[user1->num_following++] = user2;
                        user2->followers[user2->num_followers++] = user1;
                    } else {
                        assert(p1 != user1->following + user1->num_following);
                        assert(p2 != user2->followers + user2->num_followers);
                        copy(p1 + 1, user1->following + user1->num_following--, p1);
                        copy(p2 + 1, user2->followers + user2->num_followers--, p2);
                    }
                    continue;
                }
                if (op == "like" || op == "unlike") {
                    iss >> post_id;
                    if (--post_id >= user2->num_posts) {
                        oss << "Error: " << u1 << " cannot " << op << " post #" << (post_id + 1)
                            << " of " << u2 << "!\n";
                        oss << u2 << " does not have post #" << (post_id + 1) << ".";
                        throw Exception_t(INVALID_LOG, oss.str());
                    }
                    auto &post = user2->posts[post_id];
                    auto like = find(post.like_users, post.like_users + post.num_likes, user1);
                    if (op == "like") {
                        if (like != post.like_users + post.num_likes) {
                            oss << "Error: " << u1 << " cannot " << op << " post #" << (post_id + 1)
                                << " of " << u2 << "!\n";
                            oss << u1 << " has already liked post #" << (post_id + 1) << " of " << u2 << ".";
                            throw Exception_t(INVALID_LOG, oss.str());
                        }
                        assert(post.num_likes < MAX_LIKES);
                        post.like_users[post.num_likes++] = user1;
                    } else {
                        if (like == post.like_users + post.num_likes) {
                            oss << "Error: " << u1 << " cannot " << op << " post #" << (post_id + 1)
                                << " of " << u2 << "!\n";
                            oss << u1 << " has not liked post #" << (post_id + 1) << " of " << u2 << ".";
                            throw Exception_t(INVALID_LOG, oss.str());
                        }
                        copy(like + 1, post.like_users + post.num_likes--, like);
                    }
                    continue;
                }
                if (op == "comment") {
                    iss >> post_id;
                    getline(log_file, text);
                    if (--post_id >= user2->num_posts) {
                        oss << "Error: " << u1 << " cannot " << op << " post #" << (post_id + 1)
                            << " of " << u2 << "!\n";
                        oss << u2 << " does not have post #" << (post_id + 1) << ".";
                        throw Exception_t(INVALID_LOG, oss.str());
                    }
                    auto &post = user2->posts[post_id];
                    assert(post.num_comments < MAX_COMMENTS);
                    post.comments[post.num_comments++] = {text, user1};
                    continue;
                }
                if (op == "uncomment") {
                    iss >> post_id >> comment_id;
                    --comment_id;
                    if (--post_id >= user2->num_posts) {
                        oss << "Error: " << u1 << " cannot " << op << " comment #" << (comment_id + 1)
                            << " of post #" << (post_id + 1) << " posted by " << u2 << "!\n";
                        oss << u2 << " does not have post #" << (post_id + 1) << ".";
                        throw Exception_t(INVALID_LOG, oss.str());
                    }
                    auto &post = user2->posts[post_id];
                    if (comment_id >= post.num_comments) {
                        oss << "Error: " << u1 << " cannot " << op << " comment #" << (comment_id + 1)
                            << " of post #" << (post_id + 1) << " posted by " << u2 << "!\n";
                        oss << "Post #" << (post_id + 1) << " does not have comment #" << (comment_id + 1) << ".";
                        throw Exception_t(INVALID_LOG, oss.str());
                    }
                    auto &comment = post.comments[comment_id];
                    if (comment.user != user1) {
                        oss << "Error: " << u1 << " cannot " << op << " comment #" << (comment_id + 1)
                            << " of post #" << (post_id + 1) << " posted by " << u2 << "!\n";
                        oss << u1 << " is not the owner of comment #" << (comment_id + 1) << ".";
                        throw Exception_t(INVALID_LOG, oss.str());
                    }
                    copy(post.comments + comment_id + 1, post.comments + post.num_comments--,
                         post.comments + comment_id);
                    continue;
                }
                if (op == "visit") {
                    string relation;
                    if (user1 != user2) {
                        auto is_following = find(user1->following, user1->following + user1->num_following, user2)
                                            != user1->following + user1->num_following;
                        auto is_follower = find(user1->followers, user1->followers + user1->num_followers, user2)
                                           != user1->followers + user1->num_followers;
                        if (is_following) {
                            if (is_follower) relation = "friend";
                            else relation = "following";
                        } else relation = "stranger";
                    }
                    printUser(*user2, relation);
                    continue;
                }
            } catch (Exception_t &e) {
                assert(e.error == INVALID_LOG);
                cout << e.error_info << endl;
            }
        }
        log_file.close();

    } catch (Exception_t &e) {
        if (e.error == INVALID_ARGUMENT) {
            cout << "Error: Wrong number of arguments!\n";
            cout << "Usage: ./p2 <username> <logfile>" << endl;
        } else if (e.error == FILE_MISSING) {
            cout << "Error: Cannot open file " << e.error_info << "!" << endl;
        } else if (e.error == CAPACITY_OVERFLOW) {
            cout << "Error: Too many " << (e.error_info_verbose.empty() ? e.error_info : e.error_info_verbose) << "!\n";
            cout << "Maximal number of " << e.error_info << " is " << e.error_int << "." << endl;
        } else {
            assert(0);
        }
    }

#ifdef DEBUG
    std::cout.rdbuf(coutBuf);
    fout.close();
#endif
    return 0;
}
