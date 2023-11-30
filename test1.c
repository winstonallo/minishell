#include "../../include/minishell.h"

//env nicht nach alphabehet sortiert == BAUSTELLE
// static int	print_env_sorted(t_shell *data)
// {
// 	env(data);
// 	return (0);
// }
/**
 * The function "export" is used to update the environment list with the 
 * given arguments and returns a success or failure status.
 * 
 * @return either SUCCESS or FAILURE.
 */
// void	alpha_sort(t_shell *data)
// {
// 	t_env *head;

// 	t_ if (*head == NULL || (*head)->next == NULL) return ;
// }
void	print_sorted_env(t_env *head)
{
	t_env	*temp;

	temp = head;
	while (temp)
	{
		printf("declare -x %s=%s\n", temp->name, temp->line);
		temp = temp->next;
	}
}
int	export_env(t_shell *data)
{
	t_env	*current;
	t_env	*temp;
	t_env	*sorted_list;
	t_env	*head;

	head = *data->env_list;
	if (head == NULL || head->next == NULL)
		return (1);
	sorted_list = NULL;
	while (head != NULL)
	{
		current = head;
		head = current->next;
		if (sorted_list == NULL || sorted_list->name[0] >= current->name[0])
		{
			current->next = sorted_list;
			sorted_list = current;
		}
		else
		{
			temp = sorted_list;
			while (temp->next != NULL && temp->next->name[0] < current->name[0])
			{
				temp = temp->next;
			}
			current->next = temp->next;
			temp->next = current;
		}
	}
	head = sorted_list;
	print_sorted_env(head);
	return (0);
}

int	export(t_shell *data)
{
	int		i;
	char	**arg;
	int		argname;

	i = 1;
	arg = (*data->cmd_table)->args;
	if ((*data->cmd_table)->next)
		return (COMMAND_NOT_FOUND);
	if (!arg[1])
	{
		export_env(data);
		return (SUCCESS);
	}
	argname = 1;
	while (arg[i])
	{
		if (export_error(arg[i], argname) == 1)
			return (data->exit = FAILURE);
		else if (export_error(arg[i], argname) == 2)
			return (data->exit = SUCCESS);
		else if (update_env_list(data) != 0)
			return (data->exit = FAILURE);
		argname = 0;
		i++;
	}
	return (SUCCESS);
}
