#pragma once

class CSV
{
private:
	CSV() = default;
	~CSV() = default;

public:
	static bool LoadFile(const char *fileName,
						 int num, int x, int y, int *data);
};