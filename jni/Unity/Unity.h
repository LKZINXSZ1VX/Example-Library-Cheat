#include "Vector3.hpp"
#include "Vector2.hpp"
#include "Quaternion.hpp"

float NormalizeAngle (float angle){
    while (angle > 360)
        angle -= 360;
    while (angle < 0)
        angle += 360;
    return angle;
}

Vector3 NormalizeAngles (Vector3 angles){
    angles.X = NormalizeAngle (angles.X);
    angles.Y = NormalizeAngle (angles.Y);
    angles.Z = NormalizeAngle (angles.Z);
    return angles;
}

Vector3 ToEulerRad(Quaternion q1){
    float Rad2Deg = 360.0 / (M_PI * 2.0);

    float sqw = q1.W * q1.W;
    float sqx = q1.X * q1.X;
    float sqy = q1.Y * q1.Y;
    float sqz = q1.Z * q1.Z;
    float unit = sqx + sqy + sqz + sqw;
    float test = q1.X * q1.W - q1.Y * q1.Z;
    Vector3 v;

    if (test>0.4995*unit) {
        v.Y = 2.0 * atan2f (q1.Y, q1.X);
        v.X = M_PI / 2.0;
        v.Z = 0;
        return NormalizeAngles(v * Rad2Deg);
    }
    if (test<-0.4995*unit) {
        v.Y = -2.0 * atan2f (q1.Y, q1.X);
        v.X = -M_PI / 2.0;
        v.Z = 0;
        return NormalizeAngles (v * Rad2Deg);
    }
    Quaternion q(q1.W, q1.Z, q1.X, q1.Y);
    v.Y = atan2f (2.0 * q.X * q.W + 2.0 * q.Y * q.Z, 1 - 2.0 * (q.Z * q.Z + q.W * q.W)); // yaw
    v.X = asinf (2.0 * (q.X * q.Z - q.W * q.Y)); // pitch
    v.Z = atan2f (2.0 * q.X * q.Y + 2.0 * q.Z * q.W, 1 - 2.0 * (q.Y * q.Y + q.Z * q.Z)); // roll
    return NormalizeAngles (v * Rad2Deg);
}

Quaternion LookRotation(Vector3 targetLocation, Vector3 myLoc){
    return Quaternion::LookRotation((targetLocation + Vector3(0, 0.1f, 0)) - myLoc, Vector3(0, 1, 0));
}

Quaternion GetRotationToLocation(Vector3 targetLocation, float y_bias, Vector3 myLoc){
    return Quaternion::LookRotation((targetLocation + Vector3(0, y_bias, 0)) - myLoc, Vector3(0, 1, 0));
}

template <typename T>
struct monoArray
{
    void* klass;
    void* monitor;
    void* bounds;
    int   max_length;
    void* vector [1];
    int getLength()
    {
        return max_length;
    }
    T getPointer()
    {
        return (T)vector;
    }
};

template <typename T>
struct monoList {
    void *unk0;
    void *unk1;
    monoArray<T> *items;
    int size;
    int version;

    T getItems(){
        return items->getPointer();
    }
	
    int getSize(){
        return size;
    }

    int getVersion(){
        return version;
    }
};

template <typename K, typename V>
struct monoDictionary {
    void *unk0;
    void *unk1;
    monoArray<int **> *table;
    monoArray<void **> *linkSlots;
    monoArray<K> *keys;
    monoArray<V> *values;
    int touchedSlots;
    int emptySlot;
    int size;

    K getKeys() {
        return keys->getPointer();
    }

    V getValues() {
        return values->getPointer();
    }

    int getNumKeys() {
        return keys->getLength();
    }

    int getNumValues() {
        return values->getLength();
    }

    int getSize(){
        return size;
    }
};
union intfloat {
	int i;
	float f;
};

typedef struct _monoString
{
    void* klass;
    void* monitor;
    int length;    
    char chars[1];   
    int getLength()
    {
      return length;
    }
    char* getChars()
    {
        return chars;
    }
} monoString;

/*
// 1.59
	protected Transform {vps^o; // 0x1AC // Hand
	protected Transform s^uN~t; // 0x1B0 // Head
	protected Transform sqdz[Xb; // 0x1B4 // Hip
	protected Transform mB]ByDk; // 0x1B8
	protected Transform {PPLmRN; // 0x1BC
	protected Transform hFLM]|b; // 0x1C0 // Toe
	protected Transform mQlA|b; // 0x1C4
	protected Transform uFAoAB|; // 0x1C8
	protected Transform korF`oB; // 0x1CC
	protected Transform |df~k^n; // 0x1D0 // peS
	protected Transform GUcWJm; // 0x1D4 // 1.56 peD
	protected Transform Y]asp`; // 0x1D8 // dedo
	protected Transform mcbhyOv; // 0x1DC // LShoulder
	protected Transform OjNRJt; // 0x1E0 //RShoulder
*/

/*
protected Transform yFayxSS; // 0x1B8
	protected Transform JoqBDUR; // 0x1BC
	protected Transform gBb{jci; // 0x1C0
	protected Transform S~D]ly; // 0x1C4
	protected Transform lJgBpso; // 0x1C8
	protected Transform |[tt{c; // 0x1CC
	protected Transform `}Klj; // 0x1D0
	protected Transform SrnCMrP; // 0x1D4
	protected Transform jzgDN^; // 0x1D8
	protected Transform APPZcef; // 0x1DC
	protected Transform oporBaB; // 0x1E0
	protected Transform lpF[hWQ; // 0x1E4
	protected Transform yvZ[NRv; // 0x1E8
	protected Transform iuhFwSC; // 0x1EC
	protected Transform IcoOWF; // 0x1F0
*/

