/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davifern <davifern@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:01:45 by davifern          #+#    #+#             */
/*   Updated: 2024/03/02 10:47:25 by davifern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//TODO: ver o caso make && ./philo 10 310 150 100
//TODO: ver porque nesse caso ./philo 5 410 200 200 sempre o zero morre primeiro
//TODO: criar exit_error function e limitar números de até 9 dígitos
//TODO: stops when all phisolophers eat enough
//TODO: handle mutex init error, free pointers, destroy mutex etc.
//TODO: acho que faz mais sentido ter um mutex_fasting por filósofo, mas um geral em god tbm funciona
//TODO: testar com 0, 1, 5, 10 e 200 filósofos. Testar com diferentes tempos e com -1, 0, n em times_to_eat. Usar algum tester tbm
//TODO: testar data race
//DONE: Check if one philosopher died and finish execution
//DONE: Mutex the fork. O garfo tá disponível? Pego e seguro até o outro estar disponível.
//DONE: Soltar o garfo quando um deles não está disponível - No voy a hacer
//DONE: criar uma thread (outra rotina com mesmo god) que observa se os filósofos estão vivos e se um morreu imprime que ela morreu pq pense no exe: 2 filósofos
// que levam 300ms para comer e 200ms para morrer. Quando o primeiro come o segundo vai morrer em 200ms contudo como ele que vai printar
// sua morte, vai printar em 300 e não 200. make && ./philo 2 100 300 100. Isso acontece porque enquanto o 1 está comendo (com os dois garfos) o 2 está espereando sua
// vez no pthread_mutex_lock. Quando o 1 libera os garfos, 2 bloqueia o garfo e vai verificar se morreu. - OK
//DONE: talvez deva implementar mutex em all_alive. Não entendo como aparentemente funciona. Talvez tenha um data race aí. Checar com fsanitize. -> Sim,
// havia um data race nesse ponto porque ao mesmo tempo que um filósofo queria saber se todos estavam vivos, o observador estava alterando esse valor
//DONE: passar a thread para dentro do filósofo.


/* 
* pthread_mutex_lock(&god->mutex_fork[i]) : if the mutex is already locked by 
* a different thread, the calling thread will block (i.e., wait) until the mutex 
* becomes available. This means that the thread attempting to acquire the lock
* will be suspended and placed in a wait state until the thread that currently 
* holds the lock releases it. Em outras palavras, pega (bloqueia) o garfo i se
* não estiver bloqueado 

* pthread_join: é como um wait para thread. Não executa nada depois até que a
* thread i termine sua execução
*/

#include "philo.h"

int	main(int argc, char **argv)
{
	int		i;
	t_god	*god;

	if (check_input(argc, argv))
		return (1);
	god = create_god(argv);
	if (!god)
		return (-1);
	create_philos_and_start_threads(god, routine);
	//The observer
	i = 0;
	while (all_alive(god))
	{
				pthread_mutex_lock(&god->mutex_all_alive);
		while (i < god->n_philo)
		{
			if (philosopher_died(&god->philo[i]))
			{
				god->all_alive = 0;
				break ;
			}
			i++;
		}
				pthread_mutex_unlock(&god->mutex_all_alive);
		i = 0;
	}
	wait_threads(god);
	clean_and_destroy(god);
	return (0);
}
/*
	//TODO: All phisolophers eat enough?
	Código abaixo aparentemente verifica isso
	i = 0;
	int	a = 0;
	while(1)
	{
		if (god->n_times_eat < 0)
			break ;
		while (i <= god->n_philo)
		{
			if (god->philo[i].times_eaten == god->n_times_eat)
			{
				printf("philo #%d comió comió el suficiente, a = %d\n", god->philo[i].id, a);
				a++;
			}
			i++;
		}
		if (a == god->n_times_eat)
		{
			printf("Todos comieron lo suficiente\n");
			break ;
			//aqui devo terminar o programa
		}
		a = 0;
		i = 0;
	}
*/