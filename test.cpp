#include "pch.h"
#include "../TankWar2/Tank.h"
#include "../TankWar2/gameconsts.h"
#include "../TankWar2/GameField.h"
#include"../TankWar2/Walls.h"
#include <iostream>
#include <string>


class FieldTest : public ::testing::Test
{
protected:
   
	GameField gameField;

	void SetUp() override
	{
		gameField.fullingField(' ');
		std::cout << "From SetUp" << std::endl;
	}
	void TearDown()
	{
		std::cout << "From TearDown" << std::endl;
	}

};

class WallTest : public ::testing::Test
{
protected:
	
	GameField gameField;
	Walls wall{gameField.getField(), 0, 0};
	void SetUp() override
	{
		gameField.fullingField(' ');
		wall.draw(gameField.getField());
		std::cout << "From SetUp" << std::endl;
	}
	void TearDown()
	{
		std::cout << "From TearDown" << std::endl;
	}

};

class TankTest : public ::testing::Test
{
protected:

	GameField gameField;
	Tank tank{ gameField.getField()};
	void SetUp() override
	{
		gameField.fullingField(' ');
		tank.draw(gameField.getField());
		std::cout << "From SetUp" << std::endl;
	}
	void TearDown()
	{
		std::cout << "From TearDown" << std::endl;
	}

};

class ThrowTest : public ::testing::Test
{
public:
	void throwExeption(int i)
	{
		std::string t = "";
		if (i == 1)
		{
			throw t;
		}
		else
		{
			throw  std::runtime_error("");
		}
	}

};

TEST_F(ThrowTest, TestThrowRuntimeExeption)
{
	EXPECT_THROW(throwExeption(2), std::runtime_error);
}

TEST_F(ThrowTest, TestThrowStringExeption)
{
	EXPECT_THROW(throwExeption(1), std::string);
}

TEST_F(FieldTest, TestFirstElementOfField)
{
	char ch = gameField.getField()[0][0];
	EXPECT_EQ(' ', ch);
}
TEST_F(FieldTest, TestWidthField)
{
	EXPECT_EQ(25, gameField.getField().size());
	EXPECT_TRUE(gameField.getField().size() < 26);
}
TEST_F(FieldTest, TestHeigth)
{
	int size = gameField.getField()[0].size();
	EXPECT_EQ(70, size);
	EXPECT_TRUE(size < 71);
}
TEST_F(FieldTest, TestFullingField)
{
	for (auto & i: gameField.getField())
	{
		for (auto j : i)
		{
			EXPECT_EQ(' ', j);
		}
	}
}
TEST_F(WallTest, TestLeftWall)
{
	for (std::vector<char>& i : gameField.getField())
	{
			EXPECT_EQ('*', i[0]);
	}
}
TEST_F(WallTest, TestRightWall)
{
	for (std::vector<char>& i : gameField.getField())
	{
		EXPECT_EQ('*', i[width-1]);
	}
}
TEST_F(WallTest, TestUpWall)
{
	for (char i : gameField.getField()[0])
	{
		EXPECT_EQ('*', i);
	}
}
TEST_F(WallTest, TestDownWall)
{
	for (char i : gameField.getField()[height-1])
	{
		EXPECT_EQ('*', i);
	}
}
TEST_F(TankTest, TestTankPosition)
{
	for (size_t i = height / 2; i < height / 2 + heightDimensionsTank; i++)
	{
		for (size_t j = width / 2; j < width / 2 + widthDimensionsTank; j++)
		{
			EXPECT_EQ('X', gameField.getField()[i][j]);
		}
	}
	EXPECT_EQ('H', gameField.getField()[heightDimensionsTank - 2 + height / 2][widthDimensionsTank + width / 2]);
}
TEST_F(TankTest, TestTankMoveRight)
{
	tank.move(MoveType::Right);
	tank.draw(gameField.getField());
	for (size_t i = height / 2; i < height / 2 + heightDimensionsTank; i++)
	{
		for (size_t j = width / 2 + 1; j < width / 2 + widthDimensionsTank + 1; j++)
		{
			EXPECT_EQ('X', gameField.getField()[i][j]);
		}
	}
}
TEST_F(TankTest, TestTankMoveLeft)
{
	tank.move(MoveType::Left);
	tank.draw(gameField.getField());
	for (size_t i = height / 2; i < height / 2 + heightDimensionsTank; i++)
	{
		for (size_t j = width / 2 - 1; j < width / 2 + widthDimensionsTank - 1; j++)
		{
			EXPECT_EQ('X', gameField.getField()[i][j]);
		}
	}

	//EXPECT_EQ('H', gameField.getField()[heightDimensionsTank - 2 + height / 2 + 1][widthDimensionsTank + width / 2 -1 -1]);
}
TEST_F(TankTest, TestTankMoveUp)
{
	tank.move(MoveType::Up);
	tank.draw(gameField.getField());
	for (size_t i = height / 2 - 1; i < height / 2 + heightDimensionsTank - 1; i++)
	{
		for (size_t j = width / 2; j < width / 2 + widthDimensionsTank; j++)
		{
			EXPECT_EQ('X', gameField.getField()[i][j]);
		}
	}
}
TEST_F(TankTest, TestTankMoveDown)
{
	tank.move(MoveType::Down);
	tank.draw(gameField.getField());
	for (size_t i = height / 2 + 1; i < height / 2 + heightDimensionsTank + 1; i++)
	{
		for (size_t j = width / 2; j < width / 2 + widthDimensionsTank; j++)
		{
			EXPECT_EQ('X', gameField.getField()[i][j]);
		}
	}
}