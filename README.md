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

`$ git fetch <remote> [<branch>]`

## Lesson 4

Any remote repo acts similar to source repo, in a sense it just a branch with the name or link of the repo added
before each branch as to avoid conflicts. Similar to `git branch` , we have `git remote` to mange remote repos.

to view all remote repo info

`$ git remote` 
`$ git remote [--verbose]` //if too much info needed

when we clone any repo , the default repo will be represented by origin. We change it by using

`$ git remote set-url <remote_name> <new-url>`

we add few remote which is just like branches, with our customizied name , with

`$ git remote add <remote-name> <url>` // For more about [GIT URL](https://git-scm.com/docs/git-push#URLS)

To get more detail about a repo

`$ git remote show <remote-name>` // similar to `$ git show` for commits 

