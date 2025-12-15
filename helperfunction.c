int strcmp_manual(const char *a, const char *b) {
    for (int i = 0; ; i++) {
        if (a[i] != b[i] || a[i] == '\0') {
            return a[i] - b[i];
        }
    }
}

//222

void remove_newline(char *str) {
    int i = 0;
    // Find the end of string and check for \n
    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';  // Replace \n with null terminator
            break;           // Stop after first newline
        }
        i++;
    }
}