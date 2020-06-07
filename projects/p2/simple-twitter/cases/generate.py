# generate random cases

import random
import os
import shutil

# all of these are less than actual limit
# to prevent someone totally wrong

MAX_USERS = 19
MAX_POSTS = 49
MAX_COMMENTS = 49
MAX_TAGS = 4

MAX_RELATIONS = MAX_USERS * (MAX_USERS - 1) // 2
MAX_TAGS_ALL = 100

users_dir = os.path.join(os.getcwd(), 'users')


def generate_user(index, following, followers):
    user_dir = os.path.join(users_dir, 'generated-%d' % index)
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

    for post in range(1, posts_num):
        post_dir = os.path.join(posts_dir, str(post))
        tags_num = random.randint(1, MAX_TAGS)
        tags = [random.randint(1, MAX_TAGS_ALL) for i in range(1, tags_num)]
        likes_num = random.randint(1, MAX_USERS)
        likes = [i for i in range(1, MAX_USERS)]
        random.shuffle(likes)
        likes = likes[0:likes_num]
        comments_num = random.randint(1, MAX_COMMENTS)
        comments = [random.randint(1, MAX_USERS) for i in range(1, comments_num)]

        with open(post_dir, 'w') as f:
            f.write('generated-%s post-%d\n' % (index, post))
            for tag in tags:
                f.write('#tag-%d#\n' % tag)
            f.write('dsnn\n')
            f.write('%d\n' % likes_num)
            for name in likes:
                f.write('generated-%s\n' % name)
            f.write('%d\n' % comments_num)
            for name in comments:
                f.write('generated-%s\n' % name)
                f.write('dscmm\n')


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


def main():
    following, followers = generate_relations()

    for i in range(1, MAX_USERS + 1):
        generate_user(i, following[i], followers[i])


if __name__ == '__main__':
    main()
