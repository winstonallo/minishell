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
All special characters lose their meaning except for **$**, **"**, **`**, and **\\**.
```
'...'
```
All special characters lose their meaning except for **'**.




