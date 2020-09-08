int mx_strncmp(const char* s1, const char* s2, int n) {
	for (int i = 0; i < n; i++) {
		if (*s1 != *s2)
			return *s1 - *s2;
		if ((*s1 == '\0' && *s2 != '\0') || (*s1 != '\0' && *s2 == '\0'))
			return *s1 - *s2;
		s1++;
		s2++;
	}
	return 0;
}
