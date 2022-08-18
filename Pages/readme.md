# Simple web sites using GitHub
## pre-requisite
* Gh account If you don't have one go [here](https://github.com/)
    * click sign up.
    * Follow the sign up flow, for feature selection you can leave it blank
    * pick the free account
* Git client installed
## lets start with the basics
* Go to your profile page https://github.com/(username)
* Click "repositories"
* Click "new"
  * set to public and the name to (username).github.io, The name has to match
  * Click Create
* Open the cmd prompt type `cmd` 
* clone the repo
 * navigate to the location you want to clone the repo in
   * ``` git clone  https://github.com/(username)/(username).github.io.git```
* you will likely get an empty repo error, that's ok
* change to the directory
  * ` cd (username).github.io.git`
* Create a basic file
  * `echo ## Hello World > readme.md`
* push it !
  ```
    git add --all
    git commit -m "Initial commit"
    git push
    ```
* lets set the automation
  * open your profile page  
  `https://github.com/(username)/(username).github.io`
  * click settings (the gear)
  * under automation click pages
  * Make sure
    * Source is set to "deply from branch"
    * Branch is set to main
    * Theame chooser is set to your preference (ex minimal). 
* navigate to the hosted page
   `https://(username).github.io`

## Modify the code
### prerequisite 
* vscode or similar editor
### lets add some style
* toin the command prompt open vs codd 
* `code .`
* open the read me and add the following under the `# hello world`
* ```
    # H1
    ## H2
    ### H3
    ordered list
    ***
    1. First item
    2. Second item
    3. Third item

    Another 
    ---
    1. First item
    1. Second item
    1. Third item

    yet another
    ___
    1. First item
    8. Second item
    3. Third item

    and even more
    1. First item
    2. Second item
        1. Indented item
        2. Indented item
    3. Third item

    unordered
    - First item
    - Second item
    - Third item

    another way
    - First item
    - Second item
        - Indented item
        - Indented item
    - Third item

    images
    ![Tux, the Linux mascot](/assets/images/tux.png)

    urls
    <https://www.markdownguide.org>

    or 
    [More fun](https://www.markdownguide.org)

    lastly make a **bold** statement

* What do you expect to happen ?
* now lets remove all of the above and add a link to a new page
* replace the contents of  `reademe.md` with 
``` 
    ## other pages
    - [my sub page](https://github.com/(username)/(username).github.io/sub)

* create a new page called sub.html
* add the following
```
    <html>
        <body>
            <h1>h1</h1>
            <h2>h2<h2/>
            <ul>
                <li>one</li>
                <li>two</li>
            </ul>
            <hr />
            <ol>
                <li>one</li>
                <li>two</li>
            </ol>
        <body>
    </html>

* inline html

<font color="red">This text is red!</font>

## Ideas for tasks
* add a custom image
* add a table
* add different colored text
* add a line break
* add a div with an image in the background
* add a background image

* explore custom classes (css) inline in the head
```
<head>
<style>
body {
  background-color: linen;
}

h1 {
  color: maroon;
  margin-left: 40px;
}
.red{
  color: red;
}

</style>
</head>
```

## Hint 
pages need to be processed server side before they are ready to view.
Keep an eye on your build using the actions tab under settings.
- more info [Pages](https://docs.github.com/en/pages)
- more info on [markdown](https://www.markdownguide.org/basic-syntax) 

