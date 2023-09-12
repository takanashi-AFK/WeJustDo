#pragma once
#include "Engine/GameObject.h"
class FuelGauge : public GameObject
{
private:
	int hPictGauge_;
	int hPictFrame_;

	int ImageWidth;
	int ImageHeight;

	float nowFuel_, maxFuel_;


	const float GaugePositon = -0.9f;
public:
	FuelGauge(GameObject* parent);

	~FuelGauge();

	void Initialize()override;

	void Update()override;

	void Draw()override;

	void Release()override;

	void SetFuel(int _nowFuel, int _maxFuel)
	{
		nowFuel_ = _nowFuel;
		maxFuel_ = _maxFuel;
	}
};