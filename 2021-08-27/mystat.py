'''Module that computes the statistics.
Author: Huaiyu Duan (UNM)
'''
from math import sqrt
import numpy as np

def mean_std(data):
    '''Compute the mean and standard deviation (std) of the data.
    data : a list or array of data

    return : (mean, std)
    '''
    mean = sum = 0. 
    for x in data:
        mean += x
    mean /= len(data)
    for x in data:
        sum += (x - mean)**2

    return mean, sqrt(sum / len(data))

def mean_std2(data):
    '''Compute the mean and standard deviation (std) of the data using the alternative formula.
    data : a list or array of data

    return : (mean, std)
    '''
    mean = sum = 0. 
    for x in data:
        mean += x
        sum += x**2
    mean /= len(data)

    return mean, sqrt(sum/len(data) - mean**2)

def mean_std_np(data):
    '''Compute the mean and standard deviation (std) of the data without explicit for loop.
    data : 1D NumPy array

    return : (mean, std)
    '''
    mean = np.sum(data) / data.size
    std = sqrt(np.sum((data - mean)**2) / data.size)
    return mean, std

def mean_std2_np(data):
    '''Compute the mean and standard deviation (std) of the data using the alternative formula without explicit for loop.
    data : 1D NumPy array

    return : (mean, std)
    '''
    mean = np.sum(data) / data.size
    std = sqrt(np.sum(data**2) / data.size - mean**2)
    return mean, std