#include "minishell.h"

void 		set_heads(t_mshell *sv)
{
	sv->sh_head = sv->sh;
	while (sv->sh)
	{
		sv->sh->tdlst_pipe_head = sv->sh->tdlst_pipe;
		while (sv->sh->tdlst_pipe)
		{
			sv->sh->tdlst_pipe->token_head = sv->sh->tdlst_pipe->token;
			sv->sh->tdlst_pipe = sv->sh->tdlst_pipe->next;
		}
		sv->sh->tdlst_pipe = sv->sh->tdlst_pipe_head;
		sv->sh = sv->sh->next;
	}
	sv->sh = sv->sh_head;
}
