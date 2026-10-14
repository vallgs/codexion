#include "../includes/codex.h"

int	ft_is_digit(char arg)
{
	if (arg >= '0' && arg <= '9')
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (sign * result);
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_limit(const char *n)
{
	long a;
	int i;

	a = 0;
	i = 0;
	while (n[i])
	{
		a = a * 10 + (n[i] - '0');
		if (a > INT_MAX)
			return (0);
		i++;
	}
	return (1);
}

int ft_is_valid_number(char *s)
{
	int j;

	j = 0;
	if (s[j] == '\0')
	{
		fprintf(stderr, "empty argument\n");
		return (0);
	}
	while (s[j])
	{
		if (ft_is_digit(s[j]) == 0)
		{
			fprintf(stderr, "\"%s\" is not a number\n", s);
			return (0);
		}
		j++;
	}
	if (ft_limit(s) == 0)
	{
		fprintf(stderr, "%s is too high\n", s);
		return (0);
	}
	return (1);
}
