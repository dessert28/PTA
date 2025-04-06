import re

def is_chinese(char):
    return '\u4e00' <= char <= '\u9fff'

def find_abb(text):
    abb_dict = {}
    for i in range(len(text) - 2):
        if is_chinese(text[i]) and is_chinese(text[i+1]) and is_chinese(text[i+2]) and text[i] != text[i + 1] and text[i + 1] == text[i + 2]:
            abb = text[i:i + 3]
            if abb in abb_dict:
                abb_dict[abb] += 1
            else:
                abb_dict[abb] = 1
    return abb_dict

def main():
    text = input().strip()
    abb_dict = find_abb(text)
    for abb, count in abb_dict.items():
        print(f"{abb}:{count}")

if __name__ == "__main__":
    main()