static int isdigit(int c) 
{
    return (c >= '0' && c <= '9');
}

static int isalpha(int c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

int isalnum(int c) {
    return isalpha(c) || isdigit(c);
}
