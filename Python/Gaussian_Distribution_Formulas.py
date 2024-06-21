import math
from scipy.integrate import quad

mean = lambda n, p : n*p

variance_2 = lambda n, p : n*p*(1-p)

standar_deviation = lambda n, p: math.sqrt(n*p*(1-p))

binomial_probability_density = lambda n, k, p : ((math.factorial(n)/(math.factorial(k)*math.factorial(n - k) ))*p**k)*(1 - p)**(n - k) 

# Now consider a Binomial distribution. Assume that 15% 
# of the population is allergic to cats. If you randomly 
# select 60 people for a medical trial, what is the 
# probability that 7 of those people are allergic to cats?

n = 60 # samples
k = 7 # probabilidad de que 7 sean alergicas
p = 0.15 # probabilidad

print(binomial_probability_density(60, 7, 0.15))

# Like in the previous question, assume the average weight 
# of an American adult male is 180 pounds with a standard 
# deviation of 34 pounds. The distribution of weights 
# follows a normal distribution. What is the probability 
# that a man weighs somewhere between 120 and 155 pounds?

def probability_density_function(value_x):
    """_summary_

    Args:
        value_x (_type_): it is a variable of the function

    Returns:
        _type_: the function to integrate
    """
    sigma_, mu_ = 34, 180
    probability = (1/math.sqrt(2*math.pi*sigma_**2  ))*math.exp(-(((value_x - mu_)**2)/(2*sigma_**2)))
    return probability 


# es nesario encontrar el area bajo la curva por lo que se 
# integra a lo largo de 120 - 155
result, error = quad(probability_density_function, 120, 155)

print("result: {}, error: {}".format(result, error))