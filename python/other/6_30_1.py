
def main():
    #code here
    a=input().strip()
    b=int(input())
    if a=="V":
        if b<=500:
            c=b*0.85
            print('No')
        elif b<=1000:
            c=b*0.8
            print('No')
        else:
            c=b*0.75
            print('Yes')
    else:
        if b<=500:
            c=b*0.9
            print('No')
        else:
            c=b*0.9
            print('Yes')
    print(f'{c:.2f}')
    pass


if __name__ == '__main__':
    main();