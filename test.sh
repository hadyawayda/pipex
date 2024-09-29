make re
make re

# Handle case when there is a wrong number of arguments
./pipex infile "grep a" "wc -l" outfile

# # Handle case when there is an empty command
# ./pipex infile "grep a" "" outfile

# # Handle case when execve fails to find the command
# ./pipex infile "grep a" "wc -l" outfile

# Regular behaviour
# < infile grep a | wc -l > outfile

# # Same behaviour for the following 2 commands
# < infile | wc -l > outfile

# # Same behaviour for the following 2 commands
# < infile grep a | > outfile

# # Copies the input to the output
# < infile | > outfile

# # Handle case when infile is not found (return error)
# < infile grep a | wc -l > outfile

# # Handle case when outfile is not found (create it)
# < infile grep a | wc -l > outfile

make fclean
