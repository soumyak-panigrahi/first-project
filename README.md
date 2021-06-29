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

- First we do work is our local repo, it has no link what so ever with remote yet.
- Then we push our work to remote repo, to do so we have to be up to date with the remote.
 - if not, we have to `$ git fetch [<remote-name>]`, then we merge the updated work to our work.
  - This can also be done `$ git pull <remote-name> <branch-name>`, this will fetch and merge.
 - if you are, just push it to repo.
  - if you want to push, a separate branch use `$ git push <remote-name> <branch-name>`.
   - if branch exist, it will be updated.
   - if doesn't exist , it will be created with branching from the master of the repo.
  - if you want to push, a branch to update a different named remote-branch use `$ git push <remote-name> <branch-name>:<remote-branch-name>` 
- If you like to remove a remote branch `$ git push <remote-name> :<branch-name>`

Note ::
- You can always use HEAD in place of the branch-name
- while `$ git push` you use -u flag `$ git push -u <remote-name> <branch-name>` it will update the working branch in repo, so that you don't have give <branch-name> argument in pull.
- You can always update the working branch in repo using `git branch -u <remote-name> <branch-name>`  
