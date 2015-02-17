#include "stdafx.h"

#include "ColorMapPanel.h"

using namespace Crystal::Graphics;
using namespace Crystal::App;

ColorMapPanel::ColorMapPanel( wxWindow* parent, const wxPoint& position, ColorRGBAMap<float>* colorMap ) :
	wxDialog( parent, wxNewId(), "Color Map", position, wxSize( 700, 600 ) ),
	colorMap( colorMap )
{
    m_canvas = new ColorMapCanvas
		(
		this,
		wxPoint(0, 0),
		wxSize( 512, 512 ),
		colorMap
		);

	Connect( wxEVT_PAINT, wxPaintEventHandler( ColorMapPanel::OnPaint ) );


	wxButton* saveButton = new wxButton( this, wxNewId(), "保存", wxPoint( 600, 50 ) );
	Connect( saveButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColorMapPanel::OnSave ) );

	wxButton* loadButton = new wxButton( this, wxNewId(), "読み込み", wxPoint( 600, 100 ) );
	Connect( loadButton->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( ColorMapPanel::OnLoad ) );


	new wxStaticText( this, wxID_ANY, "解像度", wxPoint( 550, 150 ) );
	wxSpinCtrl* resolution = new wxSpinCtrl( this );
	resolution->SetPosition( wxPoint( 600, 150 ) );
	resolution->SetSize( 50, 25 );
	resolution->SetMin( 0 );
	resolution->SetMax( 1024 );
	resolution->SetValue( colorMap->getResolution() );

	//new wxStaticText( this, wxID_ANY, "プレビュー", wxPoint( 0, 550 ) );
	wxBitmap bmp( toImage( colorMap->getResolution(), 24 ).Rescale( 512, 24 ) );
	new wxStaticBitmap( this, wxID_ANY, bmp, wxPoint(0, 520), wxSize( 512, 24 ) );
}

wxImage ColorMapPanel::toImage(  const int width, const int height ) const
{
	const std::vector<float>& reds = colorMap->getReds();
	const std::vector<float>& greens = colorMap->getGreens();
	const std::vector<float>& blues = colorMap->getBlues();
	wxImage image( width, height );
	for( int i = 0; i < width; ++i ) {
		for( int j = 0; j < height; ++j ) {
			image.SetRGB( i, j, reds[i] * 255, greens[i] * 255, blues[i] * 255 );
			//image.SetAlpha( i, j, alphas[i] );
		}
	}
	return image;
}

void ColorMapPanel::OnPaint( wxPaintEvent& )
{
	//dc.DrawBitmap( wxBitmap( 256, 24), 100, 100 );
}

#include "../IO/ColorRGBAMapIO.h"

void ColorMapPanel::OnSave( wxCommandEvent& )
{
	wxString what = "ColorMap files (*.cmap)|*.cmap";
	wxString fileName = wxSaveFileSelector( what, "cmap" );
	if( !fileName.IsEmpty() ) {
		IO::ColorRGBAMapIO::save( *colorMap, fileName.ToStdString() );
	}
}

void ColorMapPanel::OnLoad( wxCommandEvent& )
{
	wxString what = "ColorMap files (*.cmap)|*.cmap";
	wxString fileName = wxLoadFileSelector( what, "cmap" );
	if( !fileName.IsEmpty() ) {
		IO::ColorRGBAMapIO::load( *colorMap, fileName.ToStdString() );
	}
	Refresh();
	m_canvas->Refresh();
}