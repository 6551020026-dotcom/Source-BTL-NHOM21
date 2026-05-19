#include<iostream>
#include <limits>
#include<string>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

// Template
template<class T>
class quanLy {
private:
	vector<T> ds;
public:
	void themDS(const T& x) {
		ds.push_back(x);
	}

	const vector<T>& getDS() const {
		return ds;
	}

	vector<T>& getDSRef() {
		return ds;
	}

	int sizeDS() const {
		return ds.size();
	}

	void xuat() const {
		for (int i = 0; i < ds.size(); i++) {
			const T& temp = ds[i];
			temp.xuat();
		}
	}
};

// Nguoi
class Nguoi {
protected:
	string Ten;
	string SDT;
public:
	virtual void nhap() = 0;
	virtual void xuat() const = 0;
	virtual ~Nguoi() {}
};

// Nguoi thue 
class nguoiThue : public Nguoi {
private:
	string CCCD;
	string noiChon;
public:
	void nhap() override {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nhap ten: ";
		getline(cin, Ten);
		cout << "Nhap SDT: ";
		getline(cin, SDT);
		cout << "Nhap CCCD: ";
		getline(cin, CCCD);
		cout << "Nhap noi chon: ";
		getline(cin, noiChon);
	}

	void xuat() const override {
		cout << "Ten: " << Ten << " | SDT: " << SDT
			<< " | CCCD: " << CCCD
			<< " | Noi: " << noiChon << endl;
	}
};

// Hoa don
class hoaDon {
private:
	float tongTien;
	int Thang;
	bool trangThaiTT;
public:
	hoaDon() {
		tongTien = 0;
		trangThaiTT = false;
	}

	void taoHDon() {
		float tienPhong, soDien, soNuoc;

		cout << "Nhap tien phong: ";
		cin >> tienPhong;
		cout << "Nhap thang: ";
		cin >> Thang;
		cout << "Nhap so dien: ";
		cin >> soDien;
		cout << "Nhap so nuoc: ";
		cin >> soNuoc;

		tongTien = tienPhong + soDien * 3500 + soNuoc * 18000;
		trangThaiTT = false;
	}

	void xuat() const {
		cout << "Thang " << Thang << " | " << tongTien
			<< " | " << (trangThaiTT ? "Da_TT" : "Chua_TT") << endl;
	}

	void thanhToan() {
		trangThaiTT = true;
	}

	bool chuaTra() const {
		return !trangThaiTT;
	}

	float getSumTien() const {
		return tongTien;
	}
};

// Hop dong 
class hopDong {
private:
	string ngayBatDau;
	string ngayKetThuc;
	float tienCoc;
	bool conHieuLuc;
public:
	void nhap() {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nhap ngay bat dau: ";
		getline(cin, ngayBatDau);
		cout << "Nhap ngay ket thuc: ";
		getline(cin, ngayKetThuc);
		cout << "Nhap tien coc: ";
		cin >> tienCoc;
		conHieuLuc = true;
	}

	void xuat() const {
		cout << "Hop dong:" << ngayBatDau << "->" << ngayKetThuc
			<< " | " << "Coc: " << tienCoc
			<< " | " << (conHieuLuc ? "Con hieu luc." : "Het hieu luc.") << endl;
	}
};

// Phong
enum trangThai {
	TRONG = 0,
	DA_THUE = 1
};

class Phong {
private:
	string maPhong;
	float giaPhong;
	float sucChua;
	trangThai TT;

	quanLy<nguoiThue> dsNguoi;
	quanLy<hoaDon> dsHoaDon;
	hopDong HD;
public:
	void nhap() {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Nhap ma phong: ";
		getline(cin, maPhong);
		cout << "Nhap gia phong: ";
		cin >> giaPhong;
		cout << "Nhap suc chua: ";
		cin >> sucChua;
		TT = TRONG;
	}

	string getMaPhong() {
		return maPhong;
	}

	bool isTrong() {
		return TT == TRONG;
	}

	void themNguoi() {
		if (dsNguoi.sizeDS() >= sucChua) {
			cout << "PHONG DA DAY." << endl;
			return;
		}

		nguoiThue n;
		n.nhap();
		dsNguoi.themDS(n);
		TT = DA_THUE;
	}

	void taoHopDong() {
		HD.nhap();
	}

	void taoHoaDon() {
		hoaDon h;
		h.taoHDon();
		dsHoaDon.themDS(h);
	}

	void thanhToanHDon() {
		bool found = false;
		for (int i = 0; i < dsHoaDon.sizeDS(); i++) {
			hoaDon& h = dsHoaDon.getDSRef()[i];
			if (h.chuaTra()) {
				h.thanhToan();
				found = true;
			}
		}
		if (found)
			cout << "DA THANH TOAN." << endl;
		else cout << "KHONG CO HOA DON NAO CHUA THANH TOAN." << endl;
	}

	float doanhThu() {
		float sum = 0;
		for (int i = 0; i < dsHoaDon.sizeDS(); i++) {
			const hoaDon& h = dsHoaDon.getDS()[i];
			sum += h.getSumTien();
		}
		return sum;
	}

	void xuat() {
		cout << "\nPhong " << maPhong
			<< " | " << (TT == TRONG ? "PHONG TRONG." : "PHONG DA THUE.") << endl;
		HD.xuat();
		cout << "Nguoi: " << endl;
		dsNguoi.xuat();
		cout << "Hoa don: " << endl;
		dsHoaDon.xuat();
	}
};

// Tang
class Tang {
private:
	string tenTang;
	vector<Phong> dsPhong;
public:
	void nhap() {
		cout << "Nhap ten tang: ";
		cin >> tenTang;
	}

	void themPhong() {
		Phong p;
		p.nhap();
		dsPhong.push_back(p);
	}

	vector<Phong>& getPhong() {
		return dsPhong;
	}

	void hienThiPhong() {
		for (int i = 0; i < dsPhong.size(); i++) {
			Phong& p = dsPhong[i];
			p.xuat();
		}
	}
};

// Toa nha
class toaNha {
private:
	vector<Tang> dsTang;
public:
	void themTang() {
		Tang t;
		t.nhap();
		dsTang.push_back(t);
	}

	Tang* getTang(int i) {
		if (i >= 0 && i < dsTang.size()) {
			return &dsTang[i];
		}
		return NULL;
	}

	Phong* timPhong(string ma) {
		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			for (int j = 0; j < t.getPhong().size(); j++) {
				Phong& p = t.getPhong()[j];
				if (p.getMaPhong() == ma)
					return &p;
			}
		}
		return NULL;
	}

	void hienThiALL() {
		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			t.hienThiPhong();
		}
	}

	void htPhongTrong() {
		cout << "\nDANH SACH PHONG TRONG\n";
		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			for (int j = 0; j < t.getPhong().size(); j++) {
				Phong& p = t.getPhong()[j];
				if (p.isTrong())
					p.xuat();
			}
		}
	}

	void sapXepDoanhThu() {
		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			sort(t.getPhong().begin(), t.getPhong().end(),
				[](Phong& a, Phong& b) {
					return a.doanhThu() > b.doanhThu();
				});
		}
	}

	float tongDoanhThu() {
		float S = 0;
		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			for (int j = 0; j < t.getPhong().size(); j++) {
				Phong& p = t.getPhong()[j];
				S += p.doanhThu();
			}
		}
		return S;
	}

	void saveFile() {
		ofstream f("chungcu.csv");
		if (!f.is_open()) throw runtime_error("Mo file that bai");

		for (int i = 0; i < dsTang.size(); i++) {
			Tang& t = dsTang[i];
			for (int j = 0; j < t.getPhong().size(); j++) {
				Phong& p = t.getPhong()[j];
				f << p.getMaPhong() << "," << p.doanhThu() << endl;
			}
		}
		f.close();
	}
};

// MENU 
void menu() {
	toaNha tn;
	int Chon, Tang;
	string Ma;

	do {
		cout << "\nQUAN LI CHUNG CU MINI\n";
		cout << "1. Them tang." << endl;
		cout << "2. Them phong." << endl;
		cout << "3. Them nguoi." << endl;
		cout << "4. Tao hop dong." << endl;
		cout << "5. Tao hoa don." << endl;
		cout << "6. Thanh toan." << endl;
		cout << "7. Hien thi." << endl;
		cout << "8. DS Phong trong." << endl;
		cout << "9. Sap xep doanh thu." << endl;
		cout << "10. Tong doanh thu." << endl;
		cout << "11. Luu file." << endl;
		cout << "0. Thoat." << endl;
		cout << "Chon: ";
		cin >> Chon;

		try {
			switch (Chon) {
			case 1: tn.themTang();
				break;

			case 2:
				cout << "Nhap index(vi tri) tang: ";
				cin >> Tang;
				if (tn.getTang(Tang))
					tn.getTang(Tang)->themPhong();
				else throw runtime_error("Tang khong ton tai.");
				break;

			case 3:
				cout << "Nhap ma phong: ";
				cin >> Ma;
				if (tn.timPhong(Ma))
					tn.timPhong(Ma)->themNguoi();
				else throw runtime_error("Khong tim thay phong.");
				break;

			case 4:
				cout << "Nhap ma phong: ";
				cin >> Ma;

				if (tn.timPhong(Ma))
					tn.timPhong(Ma)->taoHopDong();
				else
					throw runtime_error("Khong tim thay phong.");
				break;

			case 5:
				cout << "Nhap ma phong: ";
				cin >> Ma;
				if (tn.timPhong(Ma))
					tn.timPhong(Ma)->taoHoaDon();
				else throw runtime_error("Khong tim thay phong.");
				break;

			case 6:
				cout << "Nhap ma phong: ";
				cin >> Ma;
				if (tn.timPhong(Ma))
					tn.timPhong(Ma)->thanhToanHDon();
				else throw runtime_error("Khong tim thay phong.");
				break;

			case 7:
				tn.hienThiALL();
				break;

			case 8:
				tn.htPhongTrong();
				break;

			case 9:
				tn.sapXepDoanhThu();
				cout << "Da sap xep!" << endl;;
				break;

			case 10:
				cout << "Tong doanh thu: " << tn.tongDoanhThu() << endl;
				break;

			case 11:
				tn.saveFile();
				cout << "Da luu file!" << endl;
				break;
			}
		}
		catch (exception& e) {
			cout << "Loi: " << e.what() << endl;
		}
	} while (Chon != 0);
}

int main() {
	menu();
}
