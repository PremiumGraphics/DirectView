#pragma once

class TriangleConfigDialog : public wxDialog
{
public:
	struct Config {
		Config() : xSize(1.0), ySize(1.0)
		{}
		float xSize;
		float ySize;
	};

	TriangleConfigDialog(wxWindow* parent);

	void setConfig(const Config& config);

	Config getConfig() const;

private:
	wxSpinCtrlDouble* xSize;
	wxSpinCtrlDouble* ySize;
};
