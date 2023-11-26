from random import randint, choices

NUMBER_OF_TESTS = 100

MIN_SIZE = 400
MAX_SIZE = 500

MIN_POW = 2 ** 9
MAX_POW = 2 ** 10

def get_matrix_size():
    return randint(MIN_SIZE, MAX_SIZE), randint(MIN_SIZE, MAX_SIZE)

def print_random_matrix(width, height):
    print(width, height)
    for i in range(width):
        for j in range(height):
            print(randint(MIN_SIZE, MAX_SIZE), end=' ')
        print("")

def add():
    print("ADD")
    
    m_1_width, m_1_height = get_matrix_size()
    print_random_matrix(m_1_width, m_1_height)
    
    m_2_width, m_2_height = get_matrix_size()
    print_random_matrix(m_1_width, m_1_height)
    
    return

def multiply():
    print("MULTIPLY")
   
    m_1_width, m_1_height = get_matrix_size()
    print_random_matrix(m_1_width, m_1_height)
    
    m_2_width, m_2_height = get_matrix_size()
    print_random_matrix(m_1_height, m_1_width)
    
    return

def power():
    print("POWER", randint(MIN_POW, MAX_POW))
    
    m_1_width, m_1_height = get_matrix_size()
    print_random_matrix(m_1_width, m_1_width)
    
    return

def determinant():
    print("DETERMINANT")
    
    m_1_width, m_1_height = get_matrix_size()
    print_random_matrix(m_1_width, m_1_width)
    
    return

METHODS_ODDS_MAP = {
    add:            0,
    multiply:       0,
    power:          1,
    determinant:    0
}

methods, odds = zip(*METHODS_ODDS_MAP.items())

print(NUMBER_OF_TESTS)
for _ in range(NUMBER_OF_TESTS):
    chosen_method = choices(methods, weights=odds, k=1)[0]
    
    chosen_method()