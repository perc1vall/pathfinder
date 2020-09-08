int mx_sqrt(int x) {
	double z = x;
	double y = 1;
	while (z > y) {
		z = ((z + y) / 2);
		y = (x / z);
	}
	int res;
	res = (int)z;
	if (res * res == x)
		return res;
	return 0;
}

