/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#ifndef SERVER_TYPE_H
#define SERVER_TYPE_H

#include <string>

using namespace std;


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

/* Exception */
enum Error_t {
    INVALID_ARGUMENT,
    FILE_MISSING,
    CAPACITY_OVERFLOW,
    INVALID_LOG,
};

struct Exception_t: public exception{
    Error_t error;
    string error_info;
    string error_info_verbose;
    unsigned int error_int;

    Exception_t(Error_t err, const string& info, unsigned int error_int = 0){
        this->error = err;
        this->error_info = info;
        this->error_int = error_int;
    }

    Exception_t(Error_t err, const string& info, const string& info_verbose, unsigned int error_int = 0){
        this->error = err;
        this->error_info = info;
        this->error_info_verbose = info_verbose;
        this->error_int = error_int;
    }
};

/* Compound Types Declaration */
struct Comment_t;
struct Tag_t;
struct Post_t;
struct User_t;

/* TODO: Declare any additional compound types here */


/* Compound Types Definition */
struct Comment_t
/*
// Type: Comment_t
// ------------------
// The type Comment_t is used to represent a comment
// It consists of:
// * text: text of comment
// * user: pointer to the user who posted that comment
*/
{
    string text;
    User_t *user;
};


struct Tag_t
/*
// Type: Tag_t
// ------------------
// The type Tag_t is used to represent a tag
// It consists of:
// * tag_content: the content of the tag
// * tag_score: the score of the tag used to determine the trend
*/
{
    string tag_content;
    unsigned int tag_score;
};


struct Post_t
/*
// Type: Post_t
// ------------------
// The type Comment_t is used to represent a post
// It consists of:
// * comments: An array of comments
// * like_users: An array of pointers to the users who like this post
// * tags: An array of tag contents of this post
// * owner: A pointer to the post owner
// * title: the title of the post
// * text: the text of the post
// * num_likes: the number of likes
// * num_comments: the number of comments
*/
{
    Comment_t comments[MAX_COMMENTS];
    User_t *like_users[MAX_LIKES];
    string tags[MAX_TAGS];
    User_t *owner;
    string title;
    string text;
    unsigned int num_likes = 0;
    unsigned int num_comments = 0;
    unsigned int num_tags = 0;
};


struct User_t
/*
// Type: User_t
// ------------------
// The type Comment_t is used to represent a user
// It consists of:
// * posts: An array of posts
// * following: An array of following usernames
// * followers: An array of followers
// * name: the username of user
// * num_posts: the number of posts
// * num_following: the number of following users
// * num_follower: the number of followers
*/
{
    Post_t posts[MAX_POSTS];
    User_t *following[MAX_FOLLOWING];
    User_t *followers[MAX_FOLLOWERS];
    string username;
    unsigned int num_posts = 0;
    unsigned int num_following = 0;
    unsigned int num_followers = 0;
};


/* TODO: Define any additional compound types here */
// Hint: You might find a program driving structure "Server_t" useful.

const unsigned int MAX_TAGS_ALL = MAX_USERS * MAX_POSTS * MAX_TAGS;

struct Server_t
{
    User_t users[MAX_USERS];
    unsigned int num_users = 0;
    Tag_t tags[MAX_TAGS_ALL];
    unsigned int num_tags = 0;
};


#endif // SERVER_TYPE_H
