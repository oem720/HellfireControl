#pragma once

#include <Athena/Tests/Inits/MathInits/Math_Common.hpp>

namespace MathTests {
	void InitTests_Matrix(std::vector<TestBlock>& _vBlockList) {
		TestBlock tbBlock = TestBlock("Math Library - MatrixF");

		//Basic Funcs
		{
			tbBlock.AddTest("MatrixF Identity", [](float& _fDelta) -> const bool {
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = IdentityF(), _fDelta);

				return matRes.m_vRow0 == Vec4F(1.0f, 0.0f, 0.0f, 0.0f) &&
					   matRes.m_vRow1 == Vec4F(0.0f, 1.0f, 0.0f, 0.0f) &&
					   matRes.m_vRow2 == Vec4F(0.0f, 0.0f, 1.0f, 0.0f) &&
					   matRes.m_vRow3 == Vec4F(0.0f, 0.0f, 0.0f, 1.0f);
			});

			tbBlock.AddTest("MatrixF Transpose", [](float& _fDelta) -> const bool {
				MatrixF mat;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = Transpose(mat), _fDelta);

				return matRes.m_vRow0 == Vec4F(mat[0][0], mat[1][0], mat[2][0], mat[3][0]) &&
					   matRes.m_vRow1 == Vec4F(mat[0][1], mat[1][1], mat[2][1], mat[3][1]) &&
					   matRes.m_vRow2 == Vec4F(mat[0][2], mat[1][2], mat[2][2], mat[3][2]) &&
					   matRes.m_vRow3 == Vec4F(mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("MatrixF Operator Add 1", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							 Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							 Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							 Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				MatrixF mat2(Vec4F(8.5218f, -7.7024f, 0.1505f, -9.3739f),
							 Vec4F(7.1638f, -6.2139f, 0.9811f, -7.5381f),
							 Vec4F(-0.5996f, 3.0804f, 0.4590f, 6.4972f),
							 Vec4F(9.8390f, -3.1159f, -2.8921f, 5.0563f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Add 2", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							 Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							 Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							 Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				MatrixF mat2(Vec4F(2.6348f, -8.5711f, 4.4997f, 4.1268f),
							 Vec4F(-3.4713f, -2.0537f, -5.8232f, 2.5531f),
							 Vec4F(1.4602f, -7.8907f, 9.0620f, 1.5039f),
							 Vec4F(1.5039f, 2.6212f, -0.1953f, 2.3748f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Add 3", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							 Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							 Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							 Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				MatrixF mat2(Vec4F(-0.8979f, 0.9560f, -3.2319f, -7.7587f),
							 Vec4F(6.0345f, -1.5436f, 0.9549f, 3.4469f),
							 Vec4F(-5.8357f, -3.3380f, 1.8771f, 3.2215f),
							 Vec4F(-5.0338f, -9.0226f, -9.7934f, -5.4706f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Sub 1", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							 Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							 Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							 Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				MatrixF mat2(Vec4F(8.5218f, -7.7024f, 0.1505f, -9.3739f),
							 Vec4F(7.1638f, -6.2139f, 0.9811f, -7.5381f),
							 Vec4F(-0.5996f, 3.0804f, 0.4590f, 6.4972f),
							 Vec4F(9.8390f, -3.1159f, -2.8921f, 5.0563f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Sub 2", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							 Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							 Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							 Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				MatrixF mat2(Vec4F(2.6348f, -8.5711f, 4.4997f, 4.1268f),
							 Vec4F(-3.4713f, -2.0537f, -5.8232f, 2.5531f),
							 Vec4F(1.4602f, -7.8907f, 9.0620f, 1.5039f),
							 Vec4F(1.5039f, 2.6212f, -0.1953f, 2.3748f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Sub 3", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							 Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							 Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							 Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				MatrixF mat2(Vec4F(-0.8979f, 0.9560f, -3.2319f, -7.7587f),
							 Vec4F(6.0345f, -1.5436f, 0.9549f, 3.4469f),
							 Vec4F(-5.8357f, -3.3380f, 1.8771f, 3.2215f),
							 Vec4F(-5.0338f, -9.0226f, -9.7934f, -5.4706f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Mul Scalar 1", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				float scale = 8.5218f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat * scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixF Operator Mul Scalar 2", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				float scale = 2.6348f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = scale * mat, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixF Operator Mul Scalar 3", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				float scale = -0.8979f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat * scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixF Operator Div Scalar 1", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				float scale = 8.5218f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat / scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixF Operator Div Scalar 2", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				float scale = 2.6348f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = scale / mat, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixF Operator Div Scalar 3", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				float scale = -0.8979f;
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat / scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixF Operator Mul Vec 1", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				Vec4F vec(8.5218f, -7.7024f, 0.1505f, -9.3739f);
				Vec4F vecRes;

				HC_TIME_EXECUTION(vecRes = mat * vec, _fDelta);

				return vecRes == Vec4F(Dot(mat.m_vRow0, vec),
									   Dot(mat.m_vRow1, vec),
									   Dot(mat.m_vRow2, vec),
									   Dot(mat.m_vRow3, vec));
			});

			tbBlock.AddTest("MatrixF Operator Mul Vec 2", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				Vec4F vec(2.6348f, -8.5711f, 4.4997f, 4.1268f);
				Vec4F vecRes;

				HC_TIME_EXECUTION(vecRes = vec * mat, _fDelta);

				return vecRes == Vec4F(Dot(vec, mat.m_vRow0),
									   Dot(vec, mat.m_vRow1),
									   Dot(vec, mat.m_vRow2),
									   Dot(vec, mat.m_vRow3));
			});

			tbBlock.AddTest("MatrixF Operator Mul Vec 3", [](float& _fDelta) -> const bool {
				MatrixF mat(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				Vec4F vec(-0.8979f, 0.9560f, -3.2319f, -7.7587f);
				Vec4F vecRes;

				HC_TIME_EXECUTION(vecRes = mat * vec, _fDelta);

				return vecRes == Vec4F(Dot(mat.m_vRow0, vec),
									   Dot(mat.m_vRow1, vec),
									   Dot(mat.m_vRow2, vec),
									   Dot(mat.m_vRow3, vec));
			});

			tbBlock.AddTest("MatrixF Operator Mul 1", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(0.1476f, -5.2369f, 1.0429f, -7.3396f),
							 Vec4F(-5.6365f, -5.3076f, 7.6082f, 0.4030f),
							 Vec4F(-0.3759f, -8.0661f, -2.2055f, 9.9328f),
							 Vec4F(3.4986f, -6.0377f, 0.6125f, 3.0916f));
				MatrixF mat2(Vec4F(8.5218f, -7.7024f, 0.1505f, -9.3739f),
							 Vec4F(7.1638f, -6.2139f, 0.9811f, -7.5381f),
							 Vec4F(-0.5996f, 3.0804f, 0.4590f, 6.4972f),
							 Vec4F(9.8390f, -3.1159f, -2.8921f, 5.0563f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixF matTemp = Transpose(mat2);
				MatrixF matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4F(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Mul 2", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.1455f, 5.6358f, 1.9639f, -4.6224f),
							 Vec4F(-2.6450f, -5.1967f, 6.6617f, -7.8012f),
							 Vec4F(-0.6072f, -8.9356f, 5.6749f, -5.1604f),
							 Vec4F(-7.2739f, -9.8978f, -4.7558f, -6.8605f));
				MatrixF mat2(Vec4F(2.6348f, -8.5711f, 4.4997f, 4.1268f),
							 Vec4F(-3.4713f, -2.0537f, -5.8232f, 2.5531f),
							 Vec4F(1.4602f, -7.8907f, 9.0620f, 1.5039f),
							 Vec4F(1.5039f, 2.6212f, -0.1953f, 2.3748f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixF matTemp = Transpose(mat2);
				MatrixF matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4F(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});

			tbBlock.AddTest("MatrixF Operator Mul 3", [](float& _fDelta) -> const bool {
				MatrixF mat1(Vec4F(7.4730f, 7.1723f, -3.3981f, 7.7984f),
							 Vec4F(3.4660f, 2.3764f, -4.7535f, -6.0306f),
							 Vec4F(2.5975f, -9.1502f, 8.6513f, -2.1057f),
							 Vec4F(9.7422f, 6.3399f, -3.9505f, 0.4434f));
				MatrixF mat2(Vec4F(-0.8979f, 0.9560f, -3.2319f, -7.7587f),
							 Vec4F(6.0345f, -1.5436f, 0.9549f, 3.4469f),
							 Vec4F(-5.8357f, -3.3380f, 1.8771f, 3.2215f),
							 Vec4F(-5.0338f, -9.0226f, -9.7934f, -5.4706f));
				MatrixF matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixF matTemp = Transpose(mat2);
				MatrixF matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4F(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});
		}

		_vBlockList.push_back(tbBlock);

		tbBlock = TestBlock("Math Library - MatrixD");

		//Basic Funcs
		{
			tbBlock.AddTest("MatrixD Identity", [](float& _fDelta) -> const bool {
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = IdentityD(), _fDelta);

				return matRes.m_vRow0 == Vec4D(1.0, 0.0, 0.0, 0.0) &&
					   matRes.m_vRow1 == Vec4D(0.0, 1.0, 0.0, 0.0) &&
					   matRes.m_vRow2 == Vec4D(0.0, 0.0, 1.0, 0.0) &&
					   matRes.m_vRow3 == Vec4D(0.0, 0.0, 0.0, 1.0);
			});

			tbBlock.AddTest("MatrixF Transpose", [](float& _fDelta) -> const bool {
				MatrixD mat;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = Transpose(mat), _fDelta);

				return matRes.m_vRow0 == Vec4D(mat[0][0], mat[1][0], mat[2][0], mat[3][0]) &&
					   matRes.m_vRow1 == Vec4D(mat[0][1], mat[1][1], mat[2][1], mat[3][1]) &&
					   matRes.m_vRow2 == Vec4D(mat[0][2], mat[1][2], mat[2][2], mat[3][2]) &&
					   matRes.m_vRow3 == Vec4D(mat[0][2], mat[1][2], mat[2][2], mat[3][2]);
			});
		}

		//Arithmetic Operators
		{
			tbBlock.AddTest("MatrixD Operator Add 1", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							 Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							 Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							 Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				MatrixD mat2(Vec4D(8.5218, -7.7024, 0.1505, -9.3739),
							 Vec4D(7.1638, -6.2139, 0.9811, -7.5381),
							 Vec4D(-0.5996, 3.0804, 0.4590, 6.4972),
							 Vec4D(9.8390, -3.1159, -2.8921, 5.0563));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Add 2", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							 Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							 Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							 Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				MatrixD mat2(Vec4D(2.6348, -8.5711, 4.4997, 4.1268),
							 Vec4D(-3.4713, -2.0537, -5.8232, 2.5531),
							 Vec4D(1.4602, -7.8907, 9.0620, 1.5039),
							 Vec4D(1.5039, 2.6212, -0.1953, 2.3748));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Add 3", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							 Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							 Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							 Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				MatrixD mat2(Vec4D(-0.8979, 0.9560, -3.2319, -7.7587),
							 Vec4D(6.0345, -1.5436, 0.9549, 3.4469),
							 Vec4D(-5.8357, -3.3380, 1.8771, 3.2215),
							 Vec4D(-5.0338, -9.0226, -9.7934, -5.4706));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 + mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 + mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 + mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 + mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 + mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Sub 1", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							 Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							 Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							 Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				MatrixD mat2(Vec4D(8.5218, -7.7024, 0.1505, -9.3739),
							 Vec4D(7.1638, -6.2139, 0.9811, -7.5381),
							 Vec4D(-0.5996, 3.0804, 0.4590, 6.4972),
							 Vec4D(9.8390, -3.1159, -2.8921, 5.0563));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Sub 2", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							 Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							 Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							 Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				MatrixD mat2(Vec4D(2.6348, -8.5711, 4.4997, 4.1268),
							 Vec4D(-3.4713, -2.0537, -5.8232, 2.5531),
							 Vec4D(1.4602, -7.8907, 9.0620, 1.5039),
							 Vec4D(1.5039, 2.6212, -0.1953, 2.3748));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Sub 3", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							 Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							 Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							 Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				MatrixD mat2(Vec4D(-0.8979, 0.9560, -3.2319, -7.7587),
							 Vec4D(6.0345, -1.5436, 0.9549, 3.4469),
							 Vec4D(-5.8357, -3.3380, 1.8771, 3.2215),
							 Vec4D(-5.0338, -9.0226, -9.7934, -5.4706));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 - mat2, _fDelta);

				return matRes.m_vRow0 == mat1.m_vRow0 - mat2.m_vRow0 &&
					   matRes.m_vRow1 == mat1.m_vRow1 - mat2.m_vRow1 &&
					   matRes.m_vRow2 == mat1.m_vRow2 - mat2.m_vRow2 &&
					   matRes.m_vRow3 == mat1.m_vRow3 - mat2.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Mul Scalar 1", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				double scale = 8.5218;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat * scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixD Operator Mul Scalar 2", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				double scale = 2.6348;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = scale * mat, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixD Operator Mul Scalar 3", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				double scale = -0.8979;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat * scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 * scale &&
					   matRes.m_vRow1 == mat.m_vRow1 * scale &&
					   matRes.m_vRow2 == mat.m_vRow2 * scale &&
					   matRes.m_vRow3 == mat.m_vRow3 * scale;
			});

			tbBlock.AddTest("MatrixD Operator Div Scalar 1", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				double scale = 8.5218;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat / scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixD Operator Div Scalar 2", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				double scale = 2.6348;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = scale / mat, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixD Operator Div Scalar 3", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				double scale = -0.8979;
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat / scale, _fDelta);

				return matRes.m_vRow0 == mat.m_vRow0 / scale &&
					   matRes.m_vRow1 == mat.m_vRow1 / scale &&
					   matRes.m_vRow2 == mat.m_vRow2 / scale &&
					   matRes.m_vRow3 == mat.m_vRow3 / scale;
			});

			tbBlock.AddTest("MatrixD Operator Mul Vec 1", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				Vec4D vec(8.5218, -7.7024, 0.1505, -9.3739);
				Vec4D vecRes;

				HC_TIME_EXECUTION(vecRes = mat * vec, _fDelta);

				return vecRes == Vec4D(Dot(mat.m_vRow0, vec),
									   Dot(mat.m_vRow1, vec),
									   Dot(mat.m_vRow2, vec),
									   Dot(mat.m_vRow3, vec));
			});

			tbBlock.AddTest("MatrixD Operator Mul Vec 2", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				Vec4D vec(2.6348, -8.5711, 4.4997, 4.1268);
				Vec4D vecRes;

				HC_TIME_EXECUTION(vecRes = vec * mat, _fDelta);

				return vecRes == Vec4D(Dot(vec, mat.m_vRow0),
									   Dot(vec, mat.m_vRow1),
									   Dot(vec, mat.m_vRow2),
									   Dot(vec, mat.m_vRow3));
			});

			tbBlock.AddTest("MatrixD Operator Mul Vec 3", [](float& _fDelta) -> const bool {
				MatrixD mat(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				Vec4D vec(-0.8979, 0.9560, -3.2319, -7.7587);
				Vec4D vecRes;

				HC_TIME_EXECUTION(vecRes = mat * vec, _fDelta);

				return vecRes == Vec4D(Dot(mat.m_vRow0, vec),
									   Dot(mat.m_vRow1, vec),
									   Dot(mat.m_vRow2, vec),
									   Dot(mat.m_vRow3, vec));
			});

			tbBlock.AddTest("MatrixD Operator Mul 1", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(0.1476, -5.2369, 1.0429, -7.3396),
							 Vec4D(-5.6365, -5.3076, 7.6082, 0.4030),
							 Vec4D(-0.3759, -8.0661, -2.2055, 9.9328),
							 Vec4D(3.4986, -6.0377, 0.6125, 3.0916));
				MatrixD mat2(Vec4D(8.5218, -7.7024, 0.1505, -9.3739),
							 Vec4D(7.1638, -6.2139, 0.9811, -7.5381),
							 Vec4D(-0.5996, 3.0804, 0.4590, 6.4972),
							 Vec4D(9.8390, -3.1159, -2.8921, 5.0563));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixD matTemp = Transpose(mat2);
				MatrixD matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4D(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Mul 2", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.1455, 5.6358, 1.9639, -4.6224),
							 Vec4D(-2.6450, -5.1967, 6.6617, -7.8012),
							 Vec4D(-0.6072, -8.9356, 5.6749, -5.1604),
							 Vec4D(-7.2739, -9.8978, -4.7558, -6.8605));
				MatrixD mat2(Vec4D(2.6348, -8.5711, 4.4997, 4.1268),
							 Vec4D(-3.4713, -2.0537, -5.8232, 2.5531),
							 Vec4D(1.4602, -7.8907, 9.0620, 1.5039),
							 Vec4D(1.5039, 2.6212, -0.1953, 2.3748));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixD matTemp = Transpose(mat2);
				MatrixD matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4D(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});

			tbBlock.AddTest("MatrixD Operator Mul 3", [](float& _fDelta) -> const bool {
				MatrixD mat1(Vec4D(7.4730, 7.1723, -3.3981, 7.7984),
							 Vec4D(3.4660, 2.3764, -4.7535, -6.0306),
							 Vec4D(2.5975, -9.1502, 8.6513, -2.1057),
							 Vec4D(9.7422, 6.3399, -3.9505, 0.4434));
				MatrixD mat2(Vec4D(-0.8979, 0.9560, -3.2319, -7.7587),
							 Vec4D(6.0345, -1.5436, 0.9549, 3.4469),
							 Vec4D(-5.8357, -3.3380, 1.8771, 3.2215),
							 Vec4D(-5.0338, -9.0226, -9.7934, -5.4706));
				MatrixD matRes;

				HC_TIME_EXECUTION(matRes = mat1 * mat2, _fDelta);

				MatrixD matTemp = Transpose(mat2);
				MatrixD matComp;

				for (int iNdx = 0; iNdx < 4; ++iNdx) {
					matComp[iNdx] = Vec4D(Dot(mat1[iNdx], matTemp[0]),
										  Dot(mat1[iNdx], matTemp[1]),
										  Dot(mat1[iNdx], matTemp[2]),
										  Dot(mat1[iNdx], matTemp[3]));
				}

				return matRes.m_vRow0 == matComp.m_vRow0 &&
					   matRes.m_vRow1 == matComp.m_vRow1 &&
					   matRes.m_vRow2 == matComp.m_vRow2 &&
					   matRes.m_vRow3 == matComp.m_vRow3;
			});
		}

		_vBlockList.push_back(tbBlock);
	}
}