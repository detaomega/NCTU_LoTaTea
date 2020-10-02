//sourcea: http://sunmoon-template.blogspot.com/2019/01/DelaunayTriangulation.html
template<typename T>
struct point{
	T x,y;
	point(){}
	point(const T&x,const T&y):x(x),y(y){}
	point operator+(const point &b)const{
		return point(x+b.x,y+b.y);
	}
	point operator-(const point &b)const{
		return point(x-b.x,y-b.y);
	}
	point operator*(const T &b)const{
		return point(x*b,y*b);
	}
	point operator/(const T &b)const{
		return point(x/b,y/b);
	}
	bool operator==(const point &b)const{
		return x==b.x&&y==b.y;
	}
	T dot(const point &b)const{
		return x*b.x+y*b.y;
	}
	T cross(const point &b)const{
		return x*b.y-y*b.x;
	}
	T abs2()const{//向量長度的平方
		return dot(*this);
	}
};
template<class T>
class Delaunay{
	typedef point<T> PT;
	struct face{
		int a, b, c, tag;
		vector<int> DAG;
		face(int a,int b,int c):a(a),b(b),c(c),tag(0){}
	};
	struct edge{
		int v, fid, pre, next;
		edge(int v,int fid,int pre,int next):
			v(v),fid(fid),pre(pre),next(next){}
	};
	vector<PT> S;
	vector<face> F;
	vector<edge> E;
	int onLeft(int a, int b, int p){
		if(a<3&&b<3) return (a+1)%3==b;
		PT ba = S[b]-S[a], pa = S[p]-S[a];
		if(a<3) ba = S[a]*-1, pa = S[p]-S[b];
		if(b<3) ba = S[b];
		if(p<3) pa = S[p];
		T res = ba.cross(pa);
		return res>0 ? 1 : (res<0 ? -1 : 0);
	}
	int inTriangle(int p, int fid){
		int a = E[F[fid].a].v, b = E[F[fid].b].v;
		int c = E[F[fid].c].v, ab = onLeft(a,b,p);
		int bc = onLeft(b,c,p), ca = onLeft(c,a,p);
		if(!ab&&bc*ca>=0) return F[fid].b;
		if(!bc&&ab*ca>=0) return F[fid].c;
		if(!ca&&ab*bc>=0) return F[fid].a;
		return ab==bc&&bc==ca ? F[fid].a : -1;
	}
	int timeTag;
	int pointIn(int p, int fid = 0){
		if(F[fid].tag==timeTag) return -1;
		F[fid].tag = timeTag;
		int eid = inTriangle(p, fid);
		if(eid<0||F[fid].DAG.empty()) return eid;
		for(int v:F[fid].DAG){
			int res = pointIn(p, v);
			if(res>=0) return res;
		}
		return -2; // error!
	}
	T det3(T a11,T a12,T a13,T a21,T a22,T a23,T a31,T a32,T a33){
		return a11*(a22*a33-a32*a23)-a12*(a21*a33-a31*a23)+a13*(a21*a32-a31*a22);
	}
	int inCircle(const PT &a, const PT &b, const PT &c, const PT &p){
		T as = a.abs2(), bs = b.abs2(), cs = c.abs2(), ps = p.abs2();
		T res = a.x * det3(b.y,bs,1,c.y,cs,1,p.y,ps,1)
				-a.y * det3(b.x,bs,1,c.x,cs,1,p.x,ps,1)
				+as * det3(b.x,b.y,1,c.x,c.y,1,p.x,p.y,1)
				-det3(b.x,b.y,bs,c.x,c.y,cs,p.x,p.y,ps);
		return res<0 ? 1 : (res>0 ? -1 : 0);
	}
	void addFlipFace(int pid, int eid){
		F[E[eid].fid].DAG.emplace_back(F.size());
		F[E[eid^1].fid].DAG.emplace_back(F.size());
		 F.emplace_back(E[eid].next, E.size(), E[eid^1].pre);
		int a = F.back().a, c = F.back().c;
		E.emplace_back(pid, F.size()-1, a, c);
		E[a].pre = c;
		E[a].next = E[c].pre = F.back().b;
		E[a].fid = E[c].fid = F.size()-1;
		E[c].next = a;
	}
	void legalizeEdge(int pid,int eid){
		if(E[eid^1].fid<0) return;
		int i=E[eid].v, j=E[eid^1].v, k=E[E[eid^1].next].v;
		if(i>2&&j>2&&k<3) return;
		bool notLegal;
		if(i<3) notLegal = onLeft(pid,j,k)==1;
		else if(j<3) notLegal = onLeft(i,pid,k)==1;
		else notLegal = inCircle(S[pid], S[i], S[j], S[k])==1;
		if(notLegal){
			addFlipFace(k, eid);
			addFlipFace(pid, eid^1);
			E[eid].fid = E[eid^1].fid = -3;
			legalizeEdge(pid, E[eid^1].pre);
			legalizeEdge(pid, E[eid^1].next);
		}
	}
public:
	void init(){
		S = { PT(-1,-1), PT(1,0), PT(0,1) };
		F = { face(0,2,4) };
		E = { edge(1,0,4,2), edge(0,-1,3,5), edge(2,0,0,4),
			edge(1,-1,5,1), edge(0,0,2,0), edge(2,-1,1,3) };
		timeTag = 0;
	}
	void add(const PT& p){
		S.emplace_back(p);
		int eid = (++timeTag, pointIn(S.size()-1));
		static vector<int> fe; fe.clear();
		fe.emplace_back(E[eid].next);
		fe.emplace_back(E[eid].pre);
		if(!onLeft(E[eid^1].v, E[eid].v, S.size()-1)){
			fe.emplace_back(E[eid^1].next);
			fe.emplace_back(E[eid^1].pre);
			E[eid].fid = E[eid^1].fid = -4;
		}else fe.emplace_back(eid);
		int fn = fe.size(), pid = S.size()-1;
		for(int e:fe){
			F[E[e].fid].DAG.emplace_back(F.size());
			E[e].fid = F.size();
			E[e].next = E.size();
			 F.emplace_back(e,E.size(),0);
			E.emplace_back(pid,F.size()-1,e,0);
			E.emplace_back(E[e].v,0,0,0);
		}
		for(int i=0,j=fn-1; i<fn; j=i++){
			int last = F[E[fe[j]].fid].b^1;
			 F[E[fe[i]].fid].c = last;
			E[fe[i]].pre = last;
			E[E[fe[i]].next].next = last;
			E[last].pre = E[fe[i]].next;
			E[last].next = fe[i];
			E[last].fid = E[fe[i]].fid;
		}
		for(int e:fe) legalizeEdge(pid, e);
	}
	vector<pair<int,int>> getEdge(){
		vector<pair<int,int>> res;
		for(const auto &f:F){
			if(f.DAG.empty()){
				int a = E[f.a].v,b = E[f.b].v,c = E[f.c].v;
				if(a>2&&b>2) res.emplace_back(a-3, b-3);
				if(b>2&&c>2) res.emplace_back(b-3, c-3);
				if(c>2&&a>2) res.emplace_back(c-3, a-3);
			}
		}
		return res;
	}
};
