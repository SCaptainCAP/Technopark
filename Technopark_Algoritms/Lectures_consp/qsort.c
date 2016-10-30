qsort(a, n, ttl) //qsort with the limit of operations
{
	j = split(a, n, rnd(n))
	ttl -= n - 1;
	if (ttl > 0) {
		qsort(a, j, ttl);
		qsort(&(a[j-1]), n - j - 1, ttl);
	}
	else {
		heapsort(a, n);
		heapsort(a[j + 1], n - j + 1);
	} 
		
}
