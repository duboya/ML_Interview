import pickle

def save_params(params):
    """
    Save parameters to file
    """
    pickle.dump(params, open('params.p', 'wb'))


def load_params():
    """
    Load parameters from file
    """
    return pickle.load(open('params.p', mode='rb'))


def save_params_with_name(params, name):
    """
    Save parameters to file
    """
    pickle.dump(params, open('{}.p'.format(name), 'wb'))


def load_params_with_name(name):
    """
    Load parameters from file
    """
    return pickle.load(open('{}.p'.format(name), mode='rb'))