void
fibonacci(Monitor *mon, int s) {
	unsigned int i, n;
	int nx, ny, nw, nh;
	int nv, hrest = 0, wrest = 0, r = 1;
	unsigned int g = mon->gappx;
	Client *c;

	for(n = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next), n++);
	if(n == 0)
		return;

	nx = mon->wx + g;
	ny = mon->wy + g;
	nw = mon->ww - 2*g;
	nh = mon->wh - 2*g;

	for(i = 0, c = nexttiled(mon->clients); c; c = nexttiled(c->next)) {
		if (r) {
			if ((i % 2 && (nh - g) / 2 <= 2*c->bw)
			   || (!(i % 2) && (nw - g) / 2 <= 2*c->bw)) {
				r = 0;
			}
			if (r && i < n - 1) {
				if (i % 2) {
					nv = (nh - g) / 2;
					hrest = nh - 2*nv - g;
					nh = nv;
				} else {
					nv = (nw - g) / 2;
					wrest = nw - 2*nv - g;
					nw = nv;
				}

				if ((i % 4) == 2 && !s)
					nx += nw + g;
				else if ((i % 4) == 3 && !s)
					ny += nh + g;
			}

			if ((i % 4) == 0) {
				if (s) {
					ny += nh + g;
					nh += hrest;
				}
				else {
					nh -= hrest;
					ny -= nh + g;
				}
			}
			else if ((i % 4) == 1) {
				nx += nw + g;
				nw += wrest;
			}
			else if ((i % 4) == 2) {
				ny += nh + g;
				nh += hrest;
				if (i < n - 1)
					nw += wrest;
			}
			else if ((i % 4) == 3) {
				if (s) {
					nx += nw + g;
					nw -= wrest;
				} else {
					nw -= wrest;
					nx -= nw + g;
					nh += hrest;
				}
			}
			if (i == 0)	{
				if (n != 1) {
					nw = (mon->ww - g - 2*g) - (mon->ww - g - 2*g) * (1 - mon->mfact);
					wrest = 0;
				}
				ny = mon->wy + g;
			}
			else if (i == 1)
				nw = mon->ww - nw - g - 2*g;
			i++;
		}

		resize(c, nx, ny, nw - (2*c->bw), nh - (2*c->bw), False);
	}
}

void
dwindle(Monitor *mon) {
	fibonacci(mon, 1);
}

void
spiral(Monitor *mon) {
	fibonacci(mon, 0);
}
