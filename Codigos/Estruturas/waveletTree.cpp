// Wavelet Tree
// waveletTree: construtor
// exemplo: waveletTree wt(v.begin(), v.end(), menorValorDoIntervalo, maiorValorDoIntervalo)
// count: Conta os elementos no intervalo [l, r] que são iguais a k. O intervalo é 1-indexado.
// kth: Encontra o k-ésimo menor elemento no intervalo [l, r]. O intervalo é 1-indexado.
// lte: Conta os elementos no intervalo [l, r] que são menores ou iguais a k. O intervalo é 1-indexado.
// swap: Troca o elemento com índice i com o elemento com índice i+1. O índice é 1-indexado.
// Complexidade das operações: O(log n)

struct waveletTree {
    int lo, hi;
    waveletTree *l, *r;
    vector<int> b;

    waveletTree(vector<int>::iterator from, vector<int>::iterator to, int x, int y) {
        lo = x, hi = y;

        if(from == to or hi == lo) return;

        b.reserve(to - from + 1);
        b.push_back(0);

        int mid = (lo+hi)/2;
        auto f = [mid](int x){
			return x <= mid;
		};

        for(auto it = from; it != to; it++)
			b.push_back(b.back() + f(*it));

        auto pivot = stable_partition(from, to, f);
		l = new waveletTree(from, pivot, lo, mid);
		r = new waveletTree(pivot, to, mid+1, hi);
    }

	int count(int l, int r, int k) {
		if(l > r or k < lo or k > hi) return 0;
		if(lo == hi) return r - l + 1;
		int lb = b[l-1], rb = b[r], mid = (lo+hi)/2;
		if(k <= mid) return this->l->count(lb+1, rb, k);
		return this->r->count(l-lb, r-rb, k);
	}

	int kth(int l, int r, int k){
		if(l > r) return 0;
		if(lo == hi) return lo;
		int lb = b[l-1];
		int rb = b[r];
		int inLeft = rb - lb;
		if(k <= inLeft) return this->l->kth(lb+1, rb , k);
		return this->r->kth(l-lb, r-rb, k-inLeft);
	}

	int lte(int l, int r, int k) {
		if(l > r or k < lo) return 0;
		if(hi <= k) return r - l + 1;
		int lb = b[l-1], rb = b[r];
		return this->l->lte(lb+1, rb, k) + this->r->lte(l-lb, r-rb, k);
	}

    void swap(int i) {
        if (lo == hi or i >= b.size() or i <= 0) return;
        bool iLeft = b[i] > b[i-1];
        bool i1Left = b[i+1] > b[i];
        if (iLeft && i1Left) this->l->swap(b[i]);
        if (!iLeft && !i1Left) this->r->swap(i-b[i]);
        if (iLeft && !i1Left) b[i]--;
        if (!iLeft && i1Left) b[i]++;
    }
};