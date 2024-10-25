with open("map.map", "r") as f:
    for i in range(34):
        for j in range((60*2)-10):
            char = f.read()
            print(char, end="")
            if char == "":
                exit()
        print()
