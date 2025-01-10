make re

# Handle case when there is a wrong number of arguments
# ./pipex infile "grep a" "wc -l" outfile

# Handle case when there is an empty command
# ./pipex infile "grep a" "" outfile

# Handle case when execve fails to find the command
# ./pipex infile "grepp a" "wc -l" outfile

# Regular behaviour
# < infile grep a | wc -l > outfile

# # Same behaviour for the following 2 commands
# < infile | wc -l > outfile
# < infile grep a | > outfile

# # Copies the input to the output
# < infile | > outfile

# # Handle case when infile is not found (return error)
# < infile grep a | wc -l > outfile
# ./pipex infile "grep a" "wc -l" outfile

# # Handle case when outfile is not found (create it)
# < infile grep a | wc -l > outfile

# make fclean

# Test Cases to Try:
# ./pipex nonexistent_file "ls" "wc" outfile     # Non-existent input file
# ./pipex infile "nonexistent_cmd" "wc" outfile  # Invalid first command
# ./pipex infile "ls" "nonexistent_cmd" outfile  # Invalid second command
# ./pipex infile "ls" "wc" /root/outfile         # No permissions for outfile
# ./pipex infile "" "wc" outfile                 # Empty commands
# ./pipex infile "ls    " "wc" outfile          # Commands with spaces
# ./pipex infile "cat file | grep pattern" "wc" outfile  # Complex commands

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./pipex infile "ls" "wc" outfile
