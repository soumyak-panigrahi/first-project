# first-project
First project to learn, How Git and GitHub interacts

## Leasson 1

To make a copy or distribute a exiting project, we have to clone it by

`$ git clone URL`

NOTE :- URL stands for Uniform Resource Locator

The General format of the URL is *http://github.com/username/repo.git*

Most of the time, the git will ask for Usename and Password , if Not we can give
the info within the URL as
*http://username:password@github.com/username/repo.git*

Note :- Password and/or Username having Special Charcter, need to use the special code , eg. for @ - %40

## Lesson 2

**Provided only it has one remote repo and 1 branch**

to update the REMOTE REPOSITORY use

`$ git push`

to get updated REMOTE REPSITORY files

`$ git pull`

## Lesson 3

To see changes in the repo we have to use, this will collect and store data/objects of the branches info and
it's commit history, it can bring a few or all data if branch is not provided.

`$ git fetch <remote>`

## Lesson 4

Any remote repo acts similar to source repo, in a sense it just a branch with the name or link of the repo added
before each branch as to avoid conflicts. Similar to `git branch` , we have `git remote` to mange remote repos.

to view all remote repo info

`$ git remote` 

To view more about given remote repo

`$ git remote <remote-name> [--verbose]` 

when we clone any repo , the default repo will be represented by origin. We change it by using

`$ git remote set-url <remote_name> <new-url>`

we add few remote which is just like branches, with our customizied name , with

`$ git remote add <remote-name> <url>` // For more about [GIT URL](https://git-scm.com/docs/git-push#URLS)

To get more detail about a repo

`$ git remote show <remote-name>` // similar to `$ git show <commit-id>` for commits 

## Lesson 5

While collabrating we have to be very careful not messing up, the normal stream of flow is 

* First we do work is our local repo, it has no link what so ever with remote yet.
* Then we push our work to remote repo, to do so we have to be up to date with the remote.
    * if not, we have to `$ git fetch [<remote-name>]`, then we merge the updated work to our work.
        * This can also be done `$ git pull <remote-name> <branch-name>`, this will fetch and merge.
    * if you are, just push it to repo.
        * if you want to push, a separate branch use `$ git push <remote-name> <branch-name>`.
            * if branch exist, it will be updated.
            * if doesn't exist , it will be created with branching from the master of the repo.
    * if you want to push, a branch to update a different named remote-branch use `$ git push <remote-name> <branch-name>:<remote-branch-name>` 
* If you like to remove a remote branch `$ git push <remote-name> :<branch-name>`
    * you can also use `$ git push <remote> --delete <branch-name>` , this is more intutive.

Note ::
* You can always use HEAD in place of the branch-name
* while `$ git push` you use -u flag `$ git push -u <remote-name> <branch-name>` it will update the working branch in repo, so that you don't have give <branch-name> argument in pull.
* You can always update the working branch in repo using `git branch -u <remote-name> <branch-name>`  

## Lesson 6

To adjust commit history within the branch, we play it using `$ git reset [option] [commit-ID]`

\[option\] has Three type --soft , --mixed and --hard

* --soft, in this the HEAD will point to the commit ID , but the INDEX (Staing Area) and Working Tree is untouched.
* --mixed, is similar to --soft in regards to HEAD and Working Tree but in this the INDEX to set to match the given commit ID.
* --hard, it is little horrendous in regards to version control it changes evergthing to match that commit ID . In a way the future commit ID doesn't exist as far as the GIT knows.


Ofcousre there is safer way to **revisit** past commit ID then merge accordingly, this doesn't adjust commit history what so ever 
it just make a new branch with matching every detail to the commit ID. using

`$ git checkout -b <branch-name> [commit-ID]` , this create a new branch with given name, with it's base at that commit ID. So, that we make change and then can be merged.
 
The idea of merging is simple, the base branch doesn't have any commit after the branched point , then merging will simple add 
these commit as base one (fast-forward). But if there are commit passed from the branch-off point , this may lead to conflicts
first we have resolve it manually and then merge (Three-way).

# Lesson 7

Suppose, your working in **_local_** branch , you have a branch which is updated by someone else (ofcoure remotely).
So, first your work is to be sync with remote repo regularly (either automated or manually), once you done that it for you merge 
the changes in to your working *local* branch , if conflicts solve it . then it will create a commmit to merge, it totally fine
this how thing should be done if it a remote branch.

If you know, it a local branch then you can take some liberty to make things easy for you, by rearranging the commit as to make it linear as to increase it's readbility.

Note - () is rep. Commit , (*) is rep. changed commit of commit () 

Intial, 

```
()->()->()->() - BASE Branch
             \
             ()->()->()->() - Working Branch 
```

Suppose someone is working in the base-branch , then 

```
()->()->()->()->()->()->() - BASE Branch
             \
             ()->()->()->() - Working Branch 
```

Path-I - 

using,

```
$ git checkout working-local-branch
$ git merge bsese-branch

```

```
()->()->()->()--()-->()--->() - BASE Branch
             \              \
             ()->()->()->()->(Merge Commit) - Working Branch 
```

PATH - II

using,

```
$ git checkout working-local-branch
$ git rebase base-branch
```
```
()->()->()->()-()->()->() - BASE Branch
                        \
                        (*)->(*)->(*)->(*) - Working Branch 
```

In this path, the base is changed to the latest commit , its just like changing HEAD. But in this case you will have a lot
of liberty to change commit history inbetween.

To take the liberty use `$ git rebase -i base-branch` .

So, this should only be used in local repo , as commit history is changed. And it makes it linear , in other words your solving 
all merging conflicts so that it can be easily merged by your colleage.
