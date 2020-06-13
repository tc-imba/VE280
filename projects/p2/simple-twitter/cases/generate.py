# generate random cases

import random
import os
import shutil
import string
import math
import copy
from pprint import pprint

MAX_USERS = 20
MAX_POSTS = 50
MAX_COMMENTS = 50
MAX_TAGS = 5

MAX_RELATIONS = MAX_USERS * (MAX_USERS - 1) // 2
MAX_TAGS_ALL = 100

users_dir = os.path.join(os.getcwd(), 'users')
random.seed(280)


def random_string(min_length=8, max_length=8):
    length = random.randint(min_length, max_length)
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(length))


def random_user_not_in_set(s, user=0):
    arr = []
    for i in range(1, MAX_USERS + 1):
        if i not in s and i != user:
            arr.append(i)
    if len(arr) == 0:
        return 0
    return arr[random.randint(0, len(arr) - 1)]


def random_user_in_set(s):
    arr = list(s)
    if len(arr) == 0:
        return 0
    return arr[random.randint(0, len(arr) - 1)]


def random_user():
    return random.randint(1, MAX_USERS)


def random_bool(buckets=2):
    return random.randint(1, buckets) == 1


def generate_post(index, posts_dir, post):
    tags_num = random.randint(1, MAX_TAGS)
    tags = [random.randint(1, MAX_TAGS_ALL) for i in range(1, tags_num + 1)]
    likes_num = random.randint(1, MAX_USERS)
    likes = [i for i in range(1, MAX_USERS + 1)]
    random.shuffle(likes)
    likes = likes[0:likes_num]
    comments_num = random.randint(1, MAX_COMMENTS)
    comments = [random.randint(1, MAX_USERS) for i in range(1, comments_num + 1)]

    if posts_dir:
        post_dir = os.path.join(posts_dir, str(post))
        with open(post_dir, 'w') as f:
            f.write('generated-%s post-%d\n' % (index, post))
            for tag in tags:
                f.write('#tag-%d#\n' % tag)
            f.write('generated-%s post-%s content\n' % (index, post))
            f.write('%d\n' % likes_num)
            for name in likes:
                f.write('generated-%s\n' % name)
            f.write('%d\n' % comments_num)
            for i, name in enumerate(comments):
                f.write('generated-%s\n' % name)
                f.write('generated-%s post-%s comment-%s\n' % (index, post, i + 1))

        return {
            "tags": tags,
            "likes": set(likes),
            "comments": comments,
        }

    else:
        return {
            "tags": tags,
            "likes": set(),
            "comments": [],
        }


def generate_user(index, following, followers):
    user_name = 'generated-%d' % index
    user_dir = os.path.join(users_dir, user_name)
    posts_dir = os.path.join(user_dir, 'posts')
    user_info_dir = os.path.join(user_dir, 'user_info')

    shutil.rmtree(user_dir, ignore_errors=True)
    os.makedirs(posts_dir, exist_ok=True)
    posts_num = random.randint(1, MAX_POSTS)

    with open(user_info_dir, 'w') as f:
        f.write('%d\n' % posts_num)
        f.write('%d\n' % len(following))
        for name in following:
            f.write('generated-%s\n' % name)
        f.write('%d\n' % len(followers))
        for name in followers:
            f.write('generated-%s\n' % name)

    posts = []

    for post in range(1, posts_num + 1):
        posts.append(generate_post(index, posts_dir, post))

    return {
        "index": index,
        "name": user_name,
        "posts": posts,
        "following": set(following),
        "followers": set(followers),
    }


def generate_relations():
    relations = []
    for i in range(1, MAX_USERS + 1):
        for j in range(1, MAX_USERS + 1):
            if i != j:
                relations.append((i, j))
    random.shuffle(relations)
    relations = relations[0:MAX_RELATIONS]
    following = {}
    followers = {}
    for a, b in relations:
        if a in following:
            following[a].append(b)
        else:
            following[a] = [b]
        if b in followers:
            followers[b].append(a)
        else:
            followers[b] = [a]
    return following, followers


def generate_log(users, option):
    if option == 1 or option == 2:
        # (un)follow
        u1 = random_user()
        user1 = users[u1 - 1]
        follow = random_bool()
        if follow:
            u2 = random_user_not_in_set(user1['following'], u1)
            if u2 == 0:
                return ''
            user1['following'].add(u2)
        else:
            u2 = random_user_in_set(user1['following'])
            if u2 == 0:
                return ''
            user1['following'].remove(u2)
        user2 = users[u2 - 1]
        op = follow and 'follow' or 'unfollow'
        return '%s %s %s\n' % (user1['name'], op, user2['name'])
    elif option == 3 or option == 4:
        # (un)like
        u1 = random_user()
        user1 = users[u1 - 1]
        u2 = random_user()
        user2 = users[u2 - 1]
        posts = user2['posts']
        post_id = random.randint(1, min(math.floor(len(posts) * 1.2), MAX_POSTS))
        like = random_bool()
        op = like and 'like' or 'unlike'
        return '%s %s %s %s\n' % (user1['name'], op, user2['name'], post_id)
    elif option == 5 or option == 6:
        # (un)comment
        u1 = random_user()
        user1 = users[u1 - 1]
        u2 = random_user()
        user2 = users[u2 - 1]
        posts = user2['posts']
        post_id = random.randint(1, min(math.floor(len(posts) * 1.2), MAX_POSTS))
        post = len(posts) > post_id and posts[post_id - 1] or None
        # pprint(post)
        comment = random_bool()
        op = comment and 'comment' or 'uncomment'
        if comment:
            text = random_string(5, 25)
            # if u1 == 9 and u2 == 19 and post_id == 8:
            #     print(len(post['comments']))
            if post and len(post['comments']) < MAX_COMMENTS:
                post['comments'].append(u1)
                return '%s %s %s %s\n%s\n' % (user1['name'], op, user2['name'], post_id, text)
            elif post is None:
                return '%s %s %s %s\n%s\n' % (user1['name'], op, user2['name'], post_id, text)
            else:
                return ''
        else:
            comment_id = 1
            if not post or random_bool(4):
                comment_id = random.randint(1, MAX_COMMENTS)
            else:
                for i, u in enumerate(post['comments']):
                    if u == u1:
                        comment_id = i + 1
            if post and comment_id <= len(post['comments']) and post['comments'][comment_id - 1] == u1:
                del post['comments'][comment_id - 1]
            return '%s %s %s %s %s\n' % (user1['name'], op, user2['name'], post_id, comment_id)
    elif option == 7:
        # post/delete
        u1 = random_user()
        user1 = users[u1 - 1]
        posts = user1['posts']
        post = random_bool()
        op = post and 'post' or 'delete'
        if post:
            result = ''
            if len(posts) < MAX_POSTS:
                post = generate_post(u1, None, None)
                result += '%s %s\n' % (user1['name'], op)
                result += '%s post-logfile\n' % user1['name']
                for tag in post['tags']:
                    result += '#tag-%d#\n' % tag
                result += '%s post-logfile content\n' % user1['name']
                posts.append(post)
            return result
        else:
            post_id = random.randint(1, min(math.floor(len(posts) * 1.2), MAX_POSTS))
            if post_id <= len(posts):
                del posts[post_id - 1]
            return '%s %s %s\n' % (user1['name'], op, post_id)
    elif option == 8:
        # refresh
        u1 = random_user()
        user1 = users[u1 - 1]
        op = 'refresh'
        return '%s %s\n' % (user1['name'], op)
    elif option == 9:
        # visit
        u1 = random_user()
        user1 = users[u1 - 1]
        u2 = random_user()
        user2 = users[u2 - 1]
        op = 'visit'
        return '%s %s %s\n' % (user1['name'], op, user2['name'])
    elif option == 10:
        return 'trending %d\n' % random.randint(1, MAX_TAGS_ALL)


def generate_logfile(users, lines):
    users_temp = copy.deepcopy(users)
    with open('logfile/generated-%d' % lines, 'w') as f:
        for i in range(lines):
            op = random.randint(1, 10)
            s = generate_log(users_temp, op)
            if s:
                f.write(s)


def main():
    following, followers = generate_relations()
    users = []

    with open('username/generated', 'w') as f:
        f.write('users\n')
        for i in range(1, MAX_USERS + 1):
            f.write('generated-%d\n' % i)
            user = generate_user(i, following[i], followers[i])
            users.append(user)

    generate_logfile(users, 100)
    generate_logfile(users, 200)
    generate_logfile(users, 500)
    generate_logfile(users, 1000)

    # print(users)


if __name__ == '__main__':
    main()
