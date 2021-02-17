int ft_disp_export(t_set *set)
{
    int i;
	int x;
	int egl;

	egl = 0;
	x = -1;
	i = -1;
	ft_sort_dbtab(set);
    while (set->hide_envp[++i] != NULL)
	{
		printf("declare -x ");
		while (set->hide_envp[i][++x])
		{
			printf("%c", set->hide_envp[i][x]);
			if (set->hide_envp[i][x] == '=' && egl == 0)
			{
				printf("\"");
				egl = 1;
			}
		}
		printf("\"\n");
		x = -1;
	}
        //printf("declare -x %s\n", set->hide_envp[i]);
    return (0);
}
