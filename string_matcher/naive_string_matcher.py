def naive_string_matcher(text, pattern):
    '''
    naive string matcher: O((n-m+1)*m), n=size_t, m=size_p
    '''
    size_t = len(text)
    size_p = len(pattern)

    for i in range(size_t - size_p + 1):
        if pattern == text[i: i+size_p]: # matcher
            print("Pattern %s occurs with shift %d in %s" % (pattern, i, text))

def naive_string_matcher_acc(text, pattern):
    '''
    naive string matcher: no same char in pattern, O(n), n=size_t
    algo: skip all before shifts when find an invalid shift
    '''
    size_t = len(text)
    size_p = len(pattern)

    i = 0
    j = 0
    while i < size_t:
        if j < size_p and text[i] == pattern[j]:
            j += 1
        else:
            if j > 0: i -= 1
            j = 0
        if j == size_p:
            print("Pattern %s occurs with shift %d in %s" % (pattern, i - size_p + 1, text))
        i += 1

def naive_string_mathcer_gaps(text, pattern):
    '''
    naive string matcher: gap chars in pattern
    algo: dynamic programming
    '''
    size_t = len(text)
    size_p = len(pattern)

    

    

if __name__ == '__main__':
    naive_string_matcher('000010001010001', '0001')
    naive_string_matcher_acc('abdeabcabfabcd', 'abc')
