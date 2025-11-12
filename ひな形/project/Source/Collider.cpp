#include "Collider.h"

namespace ColliderLibrary {
    // 三角形と点の当たり判定(2Dの場合)
    // 戻り値    0:三角形の内側に点がある    1:三角形の外側に点がある
    int hittest_point_polygon_2d(VECTOR2 A, VECTOR2 B, VECTOR2 C, VECTOR2 P) {

        //線上は外とみなします。
        //ABCが三角形かどうかのチェックは省略...

        VECTOR2 AB = sub_vector(B, A);
        VECTOR2 BP = sub_vector(P, B);

        VECTOR2 BC = sub_vector(C, B);
        VECTOR2 CP = sub_vector(P, C);

        VECTOR2 CA = sub_vector(A, C);
        VECTOR2 AP = sub_vector(P, A);

        //外積    Z成分だけ計算すればよいです
        double c1 = AB.x * BP.y - AB.y * BP.x;
        double c2 = BC.x * CP.y - BC.y * CP.x;
        double c3 = CA.x * AP.y - CA.y * AP.x;

        if ((c1 > 0 && c2 > 0 && c3 > 0) || (c1 < 0 && c2 < 0 && c3 < 0)) {
            //三角形の内側に点がある
            return 0;
        }

        //三角形の外側に点がある
        return 1;

    }

    //ベクトル引き算(a-b)
    VECTOR2 sub_vector(const VECTOR2& a, const VECTOR2& b)
    {
        VECTOR2 ret;
        ret.x = a.x - b.x;
        ret.y = a.y - b.y;
        return ret;
    }
}