#include "ThreadCls.h"

bool mainThreadCls::trLisHomeCls::timedMesF(mainThreadCls::strSndV s) {
	char* x = s.pack; if (s.len < 2) return false; char a[2][3]{ {'S', 'u', '\0'}, {'V', 'R', '\0'} };
	for (char t = 0, X = *x, m = 2; t < m; t++)
		if (X == *a[t]) {
			X = x[1]; x = a[t];
			for (uint8_t T = 1, M = strbasprc::charPLen(x); T < M; T++) 
				if (X == x[T]) {
					strMpCh& p = threadCls->timedMesMpCh[T = adrs.load()];
					if (!p.begin(s)) return true;
					threadBufCls::recStruct{ 
						threadCls->threadMut[T], [](void* pMCh, void* p) {
							strSndV& X = ((strMpCh*)pMCh)->p; char*& x = X.pack;
							do {
								switch (*x) {
								case 'S': switch (x[1]) case 'u': ((trLisHomeCls*)p)->dimExF(X); break; break;
								case 'V': switch (x[1]) case 'R': if (X.len > 3) ((trLisHomeCls*)p)->timedRadF(x); break; break;
								} X.ret();
							} while (!((strMpCh*)pMCh)->end());
						}
					}.start(&p, this);
					return true;
				}
			break;
		}
	return false;
}

