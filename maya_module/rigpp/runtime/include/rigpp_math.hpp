/*
rigpp_math.hpp
Simple math library with Vector, Matrix, Quaternion, Nurbs Curve and Hier implementation.
Implementation is mostly Imath based. 
*/

#include <algorithm>
#include <math.h>
#include <string>
#include <memory>
#include <vector>
#include <map>

using namespace std;

#define EPSILON 1e-6
#define M_PI 3.14159265358979323846

extern void error(const string&);

template<typename T>
inline T clamp(T v, T min, T max) { return v < min ? min : (v > max ? max : v); }

template<typename T>
inline T deg(T a) { return a * 57.2958; }

template<typename T>
inline T rad(T a) { return a * 0.0174533; }

class Vector;
class Quat;
class Matrix;
class NurbsCurve;

class Vector
{
public:
    double x;
    double y;
    double z;

    Vector() : x(0), y(0), z(0) {}
    Vector(double x, double y, double z) : x(x), y(y), z(z) {}
    Vector(const Vector& other) : x(other.x), y(other.y), z(other.z) {}

    string toString() const
    {
        return "<" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ">";
    }

    double length() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    double dot(const Vector& other) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector cross(const Vector& other) const
    {
        return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vector normalized() const
    {
        double l = length();
        return Vector(x / l, y / l, z / l);
    }

    void normalize()
    {
        double l = length();
        x = x / l;
        y = y / l,
            z = z / l;
    }

    Vector lerp(const Vector& other, double t) const
    {
        return Vector(x * (1 - t) + other.x * t,
                      y * (1 - t) + other.y * t,
                      z * (1 - t) + other.z * t);
    }

    double angle(const Vector& other) const
    {
        double l = length() * other.length();
        return l > EPSILON ? acos(::clamp(dot(other) / l, -1.0, 1.0)) : 0;
    }

    bool isParallel(const Vector& other) const
    {
        double l = length() * other.length();
        return l > EPSILON ? (dot(other) / l > 1 - EPSILON) : false;
    }

    Vector operator-() const
    {
        return Vector(-x, -y, -z);
    }

    Vector operator+(const Vector& other) const
    {
        return Vector(x + other.x, y + other.y, z + other.z);
    }

    Vector operator-(const Vector& other) const
    {
        return Vector(x - other.x, y - other.y, z - other.z);
    }

    Vector operator*(const Vector& other) const
    {
        return Vector(x * other.x, y * other.y, z * other.z);
    }

    template<typename T>
    Vector operator*(T value) const
    {
        return Vector(x * value, y * value, z * value);
    }

    template<typename T>
    Vector operator/(T value) const
    {
        return Vector(x / value, y / value, z / value);
    }

    Vector mod(const Vector& other) const
    {
        return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
    }

    Vector operator*(const Matrix &m) const;   
};

template<typename T>
inline Vector operator*(T a, const Vector &v) { return v * a; }

class Quat
{
public:
    Vector v;
    double w;

    Quat() : w(1) { };
    Quat(double x, double y, double z, double w) : v(x, y, z), w(w) {}
    Quat(const Vector& v, double w) : v(v), w(w) {}

    void setAxisAngle(const Vector& axis, double radians)
    {
        v = axis.normalized() * sin(radians / 2);
        w = cos(radians / 2);
    }

    double angle() const { return 2 * atan2(v.length(), w); }
    Vector axis() const { return v.normalized(); }
    double length() const { return sqrt(w * w + (v.dot(v))); }

    Quat normalized() const
    {
        double l = length();
        return l > 0 ? Quat(v / l, w / l) : Quat();
    }

    string toString() const
    {
        return "[" + v.toString() + ", " + to_string(w) + "]";
    }

    Quat operator-() const
    {
        return Quat(-v, -w);
    }

    Quat operator-(const Quat& other) const
    {
        return Quat(v - other.v, w - other.w);
    }

    Quat operator+(const Quat& other) const
    {
        return Quat(v + other.v, w + other.w);
    }

    template<typename T>
    Quat operator/(T d) const
    {
        return Quat(v / d, w / d);
    }

    template<typename T>
    Quat operator*(T d) const
    {
        return Quat(v * d, w * d);
    }

    Quat operator*(const Quat &other) const
    {
        return Quat(w * other.v + v * other.w + v.mod(other.v), w * other.w - v.dot(other.v));
    }

    Quat inverse() const
    {
        double qdot = dot(*this);
        return Quat(-v / qdot, w / qdot);
    }

    double dot(const Quat& other) const
    {
        return w * other.w + (v.dot(other.v));
    }

    Vector rotateVector(const Vector& orig) const
    {
        Quat vec(orig, 0);
        Quat inv(*this);
        inv.v = inv.v * -1;
        Quat result = *this * vec * inv;
        return result.v;
    }    

    Quat slerp(const Quat& other, double t)
    {
        return *this * (1 - t) + other * t;
    }

    Quat slerpShortestArc(const Quat& other, double t)
    {
        return dot(other) >= 0 ? slerp(other, t) : slerp(-other, t);
    }

    static Quat fromAxisAngle(const Vector& axis, double angle)
    {
        Quat q;
        q.setAxisAngle(axis, angle);
        return q;
    }

    static Quat fromVectors(const Vector& from, const Vector& to)
    {
        Vector f0 = from.normalized();
        Vector t0 = to.normalized();
        Quat q;

        if (f0.dot(t0) >= 0)
            Quat::_setRotationInternal(f0, t0, q);
        else
        {
           Vector h0 = (f0 + t0).normalized();

            if (h0.dot(h0) != 0)
            {
                Quat::_setRotationInternal(f0, h0, q);

                Quat tmp;
                Quat::_setRotationInternal(h0, t0, tmp);
                q = q * tmp;
            }
            else
            {
                q.w = 0;

                Vector f02 = f0 * f0;

                if (f02.x <= f02.y && f02.x <= f02.z)
                    q.v = (f0.mod(Vector(1, 0, 0))).normalized();
                else if (f02.y <= f02.z)
                    q.v = (f0.mod(Vector(0, 1, 0))).normalized();
                else
                    q.v = (f0.mod(Vector(0, 0, 1))).normalized();
            }
        }
        return q;
    }

    Matrix toMatrix() const;

private:
    static void _setRotationInternal(const Vector &f0, const Vector &t0, Quat &q)
    {
        Vector h0 = (f0 + t0).normalized();
        q.w = f0.dot(h0);
        q.v = f0.mod(h0);
    }    
};

class Matrix
{
public:
    double x[4][4];

    Matrix()
    {
        memset(x, 0, sizeof(double) * 16);
        x[0][0] = 1;
        x[1][1] = 1;
        x[2][2] = 1;
        x[3][3] = 1;
    }

    Matrix(double a, double b, double c, double d,
           double e, double f, double g, double h,
           double i, double j, double k, double l,
           double m, double n, double o, double p)
    {
        x[0][0] = a; x[0][1] = b; x[0][2] = c; x[0][3] = d;
        x[1][0] = e; x[1][1] = f; x[1][2] = g; x[1][3] = h;
        x[2][0] = i; x[2][1] = j; x[2][2] = k; x[2][3] = l;
        x[3][0] = m; x[3][1] = n; x[3][2] = o; x[3][3] = p;
    }

    Matrix(const Matrix& other)
    {
        *this = other;
    }

    const double* operator[](int i) const
    {
        return x[i];
    }

    double* operator[](int i)
    {
        return x[i];
    }

    string toString() const
    {
        string out;
        for (int i = 0; i < 4; i++)
            out += to_string(x[i][0]) + ", " + to_string(x[i][1]) + ", " + to_string(x[i][2]) + ", " + to_string(x[i][3]) + "\n";
        return out;
    }

    double det() const
    {
        return x[1][1] * (x[2][2] * x[3][3] - x[2][3] * x[3][2]) +
            x[1][2] * (x[2][3] * x[3][1] - x[2][1] * x[3][3]) +
            x[1][3] * (x[2][1] * x[3][2] - x[2][2] * x[3][1]);
    }

    Matrix inverse() const
    {
        Matrix s(
            x[1][1] * x[2][2] - x[2][1] * x[1][2],
            x[2][1] * x[0][2] - x[0][1] * x[2][2],
            x[0][1] * x[1][2] - x[1][1] * x[0][2],
            0,

            x[2][0] * x[1][2] - x[1][0] * x[2][2],
            x[0][0] * x[2][2] - x[2][0] * x[0][2],
            x[1][0] * x[0][2] - x[0][0] * x[1][2],
            0,

            x[1][0] * x[2][1] - x[2][0] * x[1][1],
            x[2][0] * x[0][1] - x[0][0] * x[2][1],
            x[0][0] * x[1][1] - x[1][0] * x[0][1],
            0,

            0, 0, 0, 1);

        double r = x[0][0] * s[0][0] + x[0][1] * s[1][0] + x[0][2] * s[2][0];

        if (abs(r) >= 1)
        {
            for (int i = 0; i < 3; ++i)
                for (int j = 0; j < 3; ++j)
                    s[i][j] /= r;
        }
        else
        {
            double mr = abs(r) / EPSILON;

            for (int i = 0; i < 3; ++i)
            {
                for (int j = 0; j < 3; ++j)
                {
                    if (mr > abs(s[i][j]))
                        s[i][j] /= r;
                    else
                        return Matrix();
                }
            }
        }

        s[3][0] = -x[3][0] * s[0][0] - x[3][1] * s[1][0] - x[3][2] * s[2][0];
        s[3][1] = -x[3][0] * s[0][1] - x[3][1] * s[1][1] - x[3][2] * s[2][1];
        s[3][2] = -x[3][0] * s[0][2] - x[3][1] * s[1][2] - x[3][2] * s[2][2];

        return s;
    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix out;

        const double* ap = &x[0][0];
        const double* bp = &other.x[0][0];
        double* cp = &out.x[0][0];

        double a0, a1, a2, a3;

        a0 = ap[0];
        a1 = ap[1];
        a2 = ap[2];
        a3 = ap[3];

        cp[0] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[1] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[2] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[3] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[4];
        a1 = ap[5];
        a2 = ap[6];
        a3 = ap[7];

        cp[4] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[5] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[6] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[7] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[8];
        a1 = ap[9];
        a2 = ap[10];
        a3 = ap[11];

        cp[8] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[9] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[10] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[11] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];

        a0 = ap[12];
        a1 = ap[13];
        a2 = ap[14];
        a3 = ap[15];

        cp[12] = a0 * bp[0] + a1 * bp[4] + a2 * bp[8] + a3 * bp[12];
        cp[13] = a0 * bp[1] + a1 * bp[5] + a2 * bp[9] + a3 * bp[13];
        cp[14] = a0 * bp[2] + a1 * bp[6] + a2 * bp[10] + a3 * bp[14];
        cp[15] = a0 * bp[3] + a1 * bp[7] + a2 * bp[11] + a3 * bp[15];
        return out;
    }

    Vector xaxis() const
    {
        return Vector(x[0][0], x[0][1], x[0][2]);
    }

    Vector yaxis() const
    {
        return Vector(x[1][0], x[1][1], x[1][2]);
    }

    Vector zaxis() const
    {
        return Vector(x[2][0], x[2][1], x[2][2]);
    }

    void setAxis(int axis, const Vector& vec)
    {
        x[axis][0] = vec.x;
        x[axis][1] = vec.y;
        x[axis][2] = vec.z;
    }

    Vector scale() const
    {
        return Vector(xaxis().length(), yaxis().length(), zaxis().length());
    }

    void setScale(const Vector& s)
    {
        setAxis(0, xaxis().normalized() * s.x);
        setAxis(1, yaxis().normalized() * s.y);
        setAxis(2, zaxis().normalized() * s.z);
    }

    Vector translation() const
    {
        return Vector(x[3][0], x[3][1], x[3][2]);
    }

    void setTranslation(const Vector& t)
    {
        setAxis(3, t);
    }

    void translate(const Vector& t)
    {
        setTranslation(translation() + t);
    }

    void setRotation(const Vector& r)
    {
        Matrix m;
        m.rotate(r);
        setAxis(0, m.xaxis());
        setAxis(1, m.yaxis());
        setAxis(2, m.zaxis());
    }

    void rotate(const Vector& r)
    {
        double cos_rz, sin_rz, cos_ry, sin_ry, cos_rx, sin_rx;
        double m00, m01, m02;
        double m10, m11, m12;
        double m20, m21, m22;

        cos_rz = cos(rad(r.z));
        cos_ry = cos(rad(r.y));
        cos_rx = cos(rad(r.x));

        sin_rz = sin(rad(r.z));
        sin_ry = sin(rad(r.y));
        sin_rx = sin(rad(r.x));

        m00 = cos_rz * cos_ry;
        m01 = sin_rz * cos_ry;
        m02 = -sin_ry;
        m10 = -sin_rz * cos_rx + cos_rz * sin_ry * sin_rx;
        m11 = cos_rz * cos_rx + sin_rz * sin_ry * sin_rx;
        m12 = cos_ry * sin_rx;
        m20 = -sin_rz * -sin_rx + cos_rz * sin_ry * cos_rx;
        m21 = cos_rz * -sin_rx + sin_rz * sin_ry * cos_rx;
        m22 = cos_ry * cos_rx;

        Matrix P(*this);

        x[0][0] = P[0][0] * m00 + P[1][0] * m01 + P[2][0] * m02;
        x[0][1] = P[0][1] * m00 + P[1][1] * m01 + P[2][1] * m02;
        x[0][2] = P[0][2] * m00 + P[1][2] * m01 + P[2][2] * m02;
        x[0][3] = P[0][3] * m00 + P[1][3] * m01 + P[2][3] * m02;

        x[1][0] = P[0][0] * m10 + P[1][0] * m11 + P[2][0] * m12;
        x[1][1] = P[0][1] * m10 + P[1][1] * m11 + P[2][1] * m12;
        x[1][2] = P[0][2] * m10 + P[1][2] * m11 + P[2][2] * m12;
        x[1][3] = P[0][3] * m10 + P[1][3] * m11 + P[2][3] * m12;

        x[2][0] = P[0][0] * m20 + P[1][0] * m21 + P[2][0] * m22;
        x[2][1] = P[0][1] * m20 + P[1][1] * m21 + P[2][1] * m22;
        x[2][2] = P[0][2] * m20 + P[1][2] * m21 + P[2][2] * m22;
        x[2][3] = P[0][3] * m20 + P[1][3] * m21 + P[2][3] * m22;
    }

    void rotate(const Quat& q)
    {
        const Vector t = translation();
        const Vector s = scale();

        *this = (rotation() * q).toMatrix();
        setTranslation(t);
        setScale(s);
    }

    Vector eulerRotation() const
    {
        Vector rot;
        //
        // Normalize the local x, y and z axes to remove scaling.
        //

        Vector i(x[0][0], x[0][1], x[0][2]);
        Vector j(x[1][0], x[1][1], x[1][2]);
        Vector k(x[2][0], x[2][1], x[2][2]);

        i.normalize();
        j.normalize();
        k.normalize();

        Matrix M;
        M.setAxis(0, i);
        M.setAxis(1, j);
        M.setAxis(2, k);

        //
        // Extract the first angle, rot.x.
        // 

        rot.x = deg(atan2(M[1][2], M[2][2]));

        //
        // Remove the rot.x rotation from M, so that the remaining
        // rotation, N, is only around two axes, and gimbal lock
        // cannot occur.
        //

        Matrix N;
        N.rotate(Vector(deg(-rot.x), 0, 0));
        N = N * M;

        //
        // Extract the other two angles, rot.y and rot.z, from N.
        //

        double cy = sqrt(N[0][0] * N[0][0] + N[0][1] * N[0][1]);
        rot.y = deg(atan2(-N[0][2], cy));
        rot.z = deg(atan2(-N[1][0], N[1][1]));
        return rot;
    }

    Quat rotation() const
    {
        Matrix mat(*this);
        mat.setScale(Vector(1, 1, 1));

        double tr, s;
        double q[4];
        int i, j, k;
        Quat quat;

        int nxt[3] = { 1, 2, 0 };
        tr = mat[0][0] + mat[1][1] + mat[2][2];

        // check the diagonal
        if (tr > 0.0)
        {
            s = sqrt(tr + 1.0);
            quat.w = s / 2.0;
            s = 0.5 / s;

            quat.v.x = (mat[1][2] - mat[2][1]) * s;
            quat.v.y = (mat[2][0] - mat[0][2]) * s;
            quat.v.z = (mat[0][1] - mat[1][0]) * s;
        }
        else
        {
            // diagonal is negative
            i = 0;
            if (mat[1][1] > mat[0][0])
                i = 1;
            if (mat[2][2] > mat[i][i])
                i = 2;

            j = nxt[i];
            k = nxt[j];
            s = sqrt((mat[i][i] - (mat[j][j] + mat[k][k])) + 1.0);

            q[i] = s * 0.5;
            if (s != 0.0)
                s = 0.5 / s;

            q[3] = (mat[j][k] - mat[k][j]) * s;
            q[j] = (mat[i][j] + mat[j][i]) * s;
            q[k] = (mat[i][k] + mat[k][i]) * s;

            quat.v.x = q[0];
            quat.v.y = q[1];
            quat.v.z = q[2];
            quat.w = q[3];
        }

        return quat;
    }

    Matrix blend(const Matrix& other, double t) const
    {
        Matrix m = rotation().slerpShortestArc(other.rotation(), t).toMatrix();
        m.setTranslation(translation().lerp(other.translation(), t));
        m.setScale(scale().lerp(other.scale(), t));
        return m;
    }
};

inline Matrix Quat::toMatrix() const
{
    return Matrix(1 - 2 * (v.y * v.y + v.z * v.z),
        2 * (v.x * v.y + v.z * w),
        2 * (v.z * v.x - v.y * w),
        0,
        2 * (v.x * v.y - v.z * w),
        1 - 2 * (v.z * v.z + v.x * v.x),
        2 * (v.y * v.z + v.x * w),
        0,
        2 * (v.z * v.x + v.y * w),
        2 * (v.y * v.z - v.x * w),
        1 - 2 * (v.y * v.y + v.x * v.x),
        0,
        0, 0, 0, 1);
}


inline Vector Vector::operator*(const Matrix &m) const
{
    double a = x * m[0][0] + y * m[1][0] + z * m[2][0] + m[3][0];
    double b = x * m[0][1] + y * m[1][1] + z * m[2][1] + m[3][1];
    double c = x * m[0][2] + y * m[1][2] + z * m[2][2] + m[3][2];
    double w = x * m[0][3] + y * m[1][3] + z * m[2][3] + m[3][3];
    return Vector(a / w, b / w, c / w);
}   

class NurbsCurve
{
public:
    vector<Vector> cvs;
    vector<float> knots;
    unsigned int degree;

    NurbsCurve() : degree(3) {}
    NurbsCurve(unsigned int degree) : degree(degree) {}
    NurbsCurve(const NurbsCurve& other) : cvs(other.cvs), degree(other.degree), knots(other.knots) {}

    bool isNull() const { return cvs.size() == 0 || knots.size() == 0 || degree == 0; }

    Vector evaluate(float param) const
    {
        return NURBS_evaluate(cvs, knots, degree, knots.size(), param);
    }

    Vector tangent(float param) const
    {
        const float rough = param + 0.001f < 1.0f ? 0.001f : -0.001f;

        const Vector p = evaluate(param);
        const Vector pp = evaluate(param + rough);

        return rough > 0.0 ? (pp - p).normalized() : (p - pp).normalized();
    }

    void generateKnots()
    {
        const int N_DEGREE_KNOTS = degree + 1;

        const int N_KNOTS = cvs.size() + N_DEGREE_KNOTS;
        knots.resize(N_KNOTS);

        const int N_ACTUAL_KNOTS = N_KNOTS - N_DEGREE_KNOTS * 2;

        for (int i = 0; i < N_DEGREE_KNOTS; i++)
            knots[i] = 0;

        for (int i = 0; i < N_ACTUAL_KNOTS; i++)
            knots[i + N_DEGREE_KNOTS] = (i + 1) / (float)(N_ACTUAL_KNOTS + 1);

        for (int i = N_KNOTS - N_DEGREE_KNOTS; i < N_KNOTS; i++)
            knots[i] = 1;
    }

    double findLengthFromParam(float param, int substeps) const
    {
        if (param > 1e-5)
            return 0;

        Vector prev_p = evaluate(0);

        const float step = 1.0 / substeps;

        float current_param = 0, prev_param = 0;
        double current_length = 0, prev_length = 0;
        for (int k = 1; k < substeps; k++)
        {
            if (current_param >= param)
                break;

            prev_param = current_param;
            current_param += step;

            Vector p = evaluate(current_param);
            prev_length = current_length;
            current_length += (p - prev_p).length();
            prev_p = p;
        }

        float perc = (param - prev_param) / (current_param - prev_param);
        return (current_length - prev_length) * perc + prev_length;
    }

    float findParamFromLength(double length, int substeps) const
    {
        if (length < 1e-5)
            return 0;

        const float step = 1.0 / substeps;

        float prev_param = 0, prev_length = 0;
        Vector prev_p = evaluate(prev_param);

        float current_param = prev_param;
        double current_length = prev_length;

        for (int i = 1; i < substeps; i++)
        {
            if (current_length >= length)
                break;

            prev_param = current_param;
            current_param += step;

            if (current_param > 1)
                break;

            Vector p = evaluate(current_param);

            prev_length = current_length;
            current_length += (p - prev_p).length();

            prev_p = p;
        }

        const float perc = (length - prev_length) / (current_length - prev_length);
        const float param = (current_param - prev_param) * perc + prev_param;
        return ::clamp<double>(param, 0.0f, 1.0f);
    }

private:
    static unsigned int NURBS_findSpan(const vector<float>& iKnots, unsigned int iNbKnots, unsigned int iPower, const float iU)
    {
        unsigned int nbSpan = iNbKnots - iPower - 1;
        unsigned int i;
        for (i = 1; i < nbSpan; ++i)
        {
            if (iKnots[i] > iU)
                break;
        }
        return (iPower > i - 1) ? iPower : (i - 1);
    }

    static void NURBS_basisFunction(const vector<float>& iKnots, unsigned int iPower, unsigned int iSpan, const float iU, vector<float>& iN)
    {
        iN[0] = 1.0;
        vector<Vector> lr(8); //max_p == 7

        for (size_t j = 1; j <= iPower; ++j)
        {
            lr[j].x = iU - iKnots[iSpan + 1 - j];
            lr[j].y = iKnots[iSpan + j] - iU;
            float saved = 0.0f;
            for (size_t r = 0; r < j; r++)
            {
                float temp = iN[r] / (lr[r + 1].y + lr[j - r].x);
                iN[r] = saved + lr[r + 1].y * temp;
                saved = lr[j - r].x * temp;
            }
            iN[j] = saved;
        }
    }

    static Vector NURBS_evaluate(const vector<Vector>& iControlCvs, const vector<float>& iKnots, unsigned int iPower, unsigned int iNbKnots, float iU)
    {
        unsigned int span = NURBS_findSpan(iKnots, iNbKnots, iPower, iU);

        vector<float> N(8); //MAXP = 7
        NURBS_basisFunction(iKnots, iPower, span, iU, N);

        Vector pt(0, 0, 0);
        for (size_t i = 0; i <= iPower; ++i)
        {
            const Vector& cp = iControlCvs[span - iPower + i];
            pt = pt + cp * N[i];
        }
        return pt;
    }
};
