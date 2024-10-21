# String Length
string="Hare Krsna"
echo ${#string}

#Substring Extraction
string="Hare Krsna"
echo ${string:5:5}  # Extracts "World"

# String Replacement
string="Hare Krsna"
echo ${string/Krsna/Rama}  # Replaces "World" with "Bash"

string="Hello, World! Welcome to the World!"
echo ${string//World/Bash}  # Replaces all occurrences of "World" with "Bash"

# Convert to Uppercase
string="hare krsna"
echo $(echo "$string" | tr '[:lower:]' '[:upper:]')

# Convert to Lowercase
string="HARE KRSNA"
echo $(echo "$string" | tr '[:upper:]' '[:lower:]')