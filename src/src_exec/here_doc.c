// void	write_to_limiter(int *fd, char *limiter)
// {
// 	char	*line;

// 	close(fd[0]);
// 	ft_putstr_fd("pipe heredoc> ", 1);
// 	while (get_next_line(0, &line))
// 	{
// 		if (ft_strcmp(limiter, line) == 0)
// 		{
// 			free(line);
// 			close(fd[1]);
// 			exit(EXIT_SUCCESS);
// 		}
// 		ft_putstr_fd("pipe heredoc> ", 1);
// 		if (write(fd[1], line, ft_strlen(line)) == -1)
// 			perror("ERROR - 11");
// 		if (write(fd[1], "\n", 1) == -1)
// 			perror("ERROR - 12");
// 		free(line);
// 	}
// 	free(line);
// 	close(fd[1]);
// 	ft_perror("ERROR - 13");
// }

// void	here_doc(int argc, char *argv[])
// {
// 	int		fd[2];
// 	int		pid;

// 	if (argc < 6)
// 		ft_error("Error: wrong count of arguments");
// 	if (pipe(fd) == -1)
// 		perror("ERROR - 9");
// 	pid = fork();
// 	if (pid == -1)
// 		ft_perror("ERROR - 10");
// 	if (pid == 0)
// 		write_to_limiter(fd, argv[2]);
// 	else
// 	{
// 		close(fd[1]);
// 		if (dup2(fd[0], STDIN_FILENO) == -1)
// 			ft_perror("ERROR - 14");
// 		close(fd[0]);
// 		waitpid(pid, NULL, 0);
// 	}
// }
