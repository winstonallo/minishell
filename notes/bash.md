# Bash

## How does Bash parse a command line?

### Step 1: Read data to execute

Bash reads the script/commands **line by line**.
If the line ends with a backslash, Bash reads the
next line as well. (probably not important for this project)

### Step 2: Process quotes

Bash goes through the line in search of quotes, the first quote it finds triggers
a 'quoted' status for all characters until the next quote of the same type.

```
"..."
```
All special characters lose their meaning except for **$**, **"**, **`**, **backslash**.
```
'...'
```
All special characters lose their meaning except for **'**.
```
INPUT
$ echo 'Back\Slash $dollar "Quote"'
OUTPUT
Back\Slash $dollar "Quote"
```
Since the backslash loses its ability to cancel special characters, this will prompt you
for the next line:
```
INPUT
$ echo 'Bad\'Idea'
GET PROMPT BACK
>
```
The second quote that we were trying to escape with the backslash actually closed the quoted state,
and the last one reopened it, which is why we are missing one quote.


### Step 3: Parse special operators

Redirection operators are removed from the command line, other operators are replaced by their result.

### Step 4: Perform expansions

Most common expansion is $PARAMETER.
```
INPUT
echo "$PWD has these files that match *.txt :" *.txt
OUTPUT
/home/abied-ch/docs has these files that match *.txt : bar.txt foo.txt
```

### Step 5: Split the command into command name and arguments

The name of the command Bash has to execute is **always** the first word in the command line.
















