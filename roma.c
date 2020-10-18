pipe(data->old_pipe);
		pid = fork();
		if (!pid)
		{
			/* пайп работает, но пока что я не обработал его совмещение с < > , так что осторожней! */
			if (index != data->count_of_process - 1)
			{
				close(data->old_pipe[0]);
				dup2(data->old_pipe[1], 1);
				close(data->old_pipe[1]);
			}
			status = execute_child(func, exec, data);
		}
		else if (pid < 0)
			debug_exit();
		else
		{
			if (index != data->count_of_process - 1)
			{
				close(data->old_pipe[1]);
				dup2(data->old_pipe[0], 0);
				close(data->old_pipe[0]);
			}
			data->current_process = pid;
			wait(&pid);
			data->current_process = 0;
		}
