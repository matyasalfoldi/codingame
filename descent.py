while True:
    tallest = -1
    index = -1
    for i in range(8):
        mountain_h = int(input())
        if mountain_h > tallest:
            tallest = mountain_h
            index = i
    print(index)
