int main(int argc, char const *argv[])
{
	/* code */
	int N =0, M = 0;
	while (scanf("%d %d", &N, &M)) {
		for (int i = 0; i < N; i++) {
			scanf("%d", &A[i]);
			A[i]--;
		}
		long long investion = 0;
		memset(bucket, 0, sizeof(bucket));
		memset(space.X, -1, sizeof(space.X));
		memset(space.Y, -1, sizeof(space.Y));
		
		for (int i = 0; i < N; i++) {
			add(i, A[i]);
			investion += inv(i, A[i]);
		}

		while (M--) {
			int index = 0;
			scanf("%d", &index);
			index--;
			printf("%lld\n", investion);
			investion -= inv(space.X[index], index);
			remove(space.X[index], index);
		}
	}
	return 0;
}