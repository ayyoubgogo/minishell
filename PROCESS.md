## Git !

<br>

![handshake](assets/handshake.gif)

<br>

1. Create the Git Repo (Done!)
2. Init the repo in your desired dir:
```sh
git init
... etc
``` 
3. Create Additional Branches
4. Create two new branches, `parse` and `exec` for the parsing and execution
```sh
git checkout -b parse # moi hh
git checkout -b exec # toi hh
```
5. As we make progress, we'll commit the changes to the branches
```sh
git add
git commit -m "sigfolt tfo hh"
```
6. Once both parts are completed and tested, we can merge both branches to the main !
```sh
git checkout main # hna ghadi n switchi ll main branch
git merge parse # ghadi n mergi lbranch ta3i (parse)
git merge exec # same for your's
```
7. Finally, push ... >>>
```sh
git push origin main
```

