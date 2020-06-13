/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/23/2020.
 * All rights reserved.
 */

#include "server_type.h"

#include <vector>
#include <string>

// https://github.com/tc-imba/VE482-p2/blob/master/src/formatter.h

template<typename T>
static inline std::string to_string(std::vector<T> &vec) {
    std::string str;
    for (const auto &val : vec) {
        str += std::to_string(val) + " ";
    }
    return str;
}

template<typename T>
static inline std::string to_string(T t) {
    return std::to_string(t);
}

template<typename T>
inline std::string operator%(std::string format, T t) {
    auto ind = format.find('?');
    if (ind == 0 || format[ind - 1] != '\\') {
        format.replace(ind, 1, to_string(t));
    }
    return format;
}

template<>
inline std::string operator%(std::string format, std::string s) {
    auto ind = format.find('?');
    if (ind == 0 || format[ind - 1] != '\\') {
        format.replace(ind, 1u, s);
    }
    return format;
}

template<>
inline std::string operator%(std::string format, const char *s) {
    auto ind = format.find('?');
    if (ind == 0 || format[ind - 1] != '\\') {
        format.replace(ind, 1u, s);
    }
    return format;
}

inline std::string operator ""_f(const char *str, size_t size) {
    return std::string(str);
}


class SimpleTwitterException : public std::exception {
protected:
    std::string info;
public:
    [[nodiscard]] const char *what() const noexcept override { return info.c_str(); };

    enum Type {
        NOT_EXIST,
        NOT_OWNER,
        ALREADY_DONE,
        NOT_DONE,
    };
};

class InvalidArgumentException : public SimpleTwitterException {
public:
    InvalidArgumentException() {
        info = "Error: Wrong number of arguments!\n";
        info += "Usage: ./p2 <username> <logfile>";
    }
};

class FileMissingException : public SimpleTwitterException {
public:
    explicit FileMissingException(const std::string &filename) {
        info = "Error: Cannot open file ?!"_f % filename;
    }
};

class TooManyUsersException : public SimpleTwitterException {
public:
    TooManyUsersException() {
        info = "Error: Too many users!\n";
        info += "Maximal number of users is ?."_f % MAX_USERS;
    }
};

class TooManyPostsException : public SimpleTwitterException {
public:
    explicit TooManyPostsException(const std::string &user) {
        info = "Error: Too many posts for user ?!\n"_f % user;
        info += "Maximal number of posts is ?."_f % MAX_POSTS;
    }
};

class TooManyFollowingsException : public SimpleTwitterException {
public:
    explicit TooManyFollowingsException(const std::string &user) {
        info = "Error: Too many followings for user ?!\n"_f % user;
        info += "Maximal number of followings is ?."_f % MAX_FOLLOWING;
    }
};

class TooManyFollowersException : public SimpleTwitterException {
public:
    explicit TooManyFollowersException(const std::string &user) {
        info = "Error: Too many followers for user ?!\n"_f % user;
        info += "Maximal number of followers is ?."_f % MAX_FOLLOWERS;
    }
};

class TooManyTagsException : public SimpleTwitterException {
public:
    explicit TooManyTagsException(const std::string &post) {
        info = "Error: Too many tags for post ?!\n"_f % post;
        info += "Maximal number of tags is ?."_f % MAX_TAGS;
    }
};

class TooManyLikesException : public SimpleTwitterException {
public:
    explicit TooManyLikesException(const std::string &post) {
        info = "Error: Too many likes for post ?!\n"_f % post;
        info += "Maximal number of likes is ?."_f % MAX_LIKES;
    }
};

class TooManyCommentsException : public SimpleTwitterException {
public:
    explicit TooManyCommentsException(const std::string &post) {
        info = "Error: Too many comments for post ?!\n"_f % post;
        info += "Maximal number of comments is ?."_f % MAX_COMMENTS;
    }
};

class LikeException : public SimpleTwitterException {
public:
    LikeException(const std::string &user1, const std::string &user2, std::size_t postId, Type type) {
        ++postId;
        info = "Error: ? cannot like post #? of ?!\n"_f % user1 % postId % user2;
        if (type == NOT_EXIST) {
            info += "? does not have post #?." % user2 % postId;
        } else {
            info += "? has already liked post #? of ?." % user1 % postId % user2;
        }
    }
};

class UnLikeException : public SimpleTwitterException {
public:
    UnLikeException(const std::string &user1, const std::string &user2, std::size_t postId, Type type) {
        ++postId;
        info = "Error: ? cannot unlike post #? of ?!\n"_f % user1 % postId % user2;
        if (type == NOT_EXIST) {
            info += "? does not have post #?." % user2 % postId;
        } else {
            info += "? has not liked post #? of ?." % user1 % postId % user2;
        }
    }
};

class CommentException : public SimpleTwitterException {
public:
    CommentException(const std::string &user1, const std::string &user2, std::size_t postId) {
        ++postId;
        info = "Error: ? cannot comment post #? of ?!\n"_f % user1 % postId % user2;
        info += "? does not have post #?." % user2 % postId;
    }
};


class UnCommentException : public SimpleTwitterException {
public:
    UnCommentException(const std::string &user1, const std::string &user2,
                       std::size_t postId, std::size_t commentId, Type type) {
        ++postId;
        ++commentId;
        info = "Error: ? cannot uncomment comment #? of post #? posted by ?!\n"_f
               % user1 % commentId % postId % user2;
        if (type == NOT_EXIST) {
            info += "? does not have post #?." % user2 % postId;
        } else if (type == NOT_DONE) {
            info += "Post #? does not have comment #?."_f % postId % commentId;
        } else {
            info += "? is not the owner of comment #?."_f % user1 % commentId;
        }
    }
};

class DeletePostException : public SimpleTwitterException {
public:
    DeletePostException(const std::string &user, std::size_t postId) {
        ++postId;
        info = "Error: ? cannot delete post #?!\n"_f % user % postId;
        info += "? does not have post #?."_f % user % postId;
    }
};

class FollowException : public SimpleTwitterException {
public:
    FollowException(const std::string &user1, const std::string &user2) {

    }
};

class UnFollowException : public SimpleTwitterException {
public:
    UnFollowException(const std::string &user1, const std::string &user2) {

    }
};

class UserNotFoundException : public SimpleTwitterException{
public:
    explicit UserNotFoundException(const std::string &user) {
        info = "Error: User ? cannot be found!" % user;
    }
};

class InvalidOperationException : public SimpleTwitterException {
public:
    explicit InvalidOperationException(const std::string &operation) {
        info = "Error: Operation ? is not defined!"_f % operation;
    }
};
