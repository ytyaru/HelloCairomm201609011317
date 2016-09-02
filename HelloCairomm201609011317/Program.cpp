#include <gtkmm.h>
#include <glibmm.h>
#include <string>
class MyDrawArea : public Gtk::DrawingArea
{
public:
    MyDrawArea(){}
protected:
    virtual bool on_expose_event( GdkEventExpose* e );
};
bool MyDrawArea::on_expose_event( GdkEventExpose* event )
{
	int width = get_width();
	int height =get_height();
	double y = 10;

	Cairo::RefPtr< Cairo::Context > cairoctx = get_window()->create_cairo_context();

	// 解像度取得
	double resolution = get_pango_context()->get_resolution();

	// 背景の塗りつぶし
	Gdk::Cairo::set_source_color( cairoctx, Gdk::Color( "black" ) ); 
	cairoctx->paint();

	std::string str = "あいうえお";
	Glib::ustring text = Glib::locale_to_utf8(str);
	
	cairoctx->select_font_face( "Serif", Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL );
	cairoctx->set_font_size( 20 * resolution / 72 );  // pixel = pt * DPI/72

	// 色指定
	Gdk::Cairo::set_source_color( cairoctx, Gdk::Color( "white" ) ); 

	// extents取得
	Cairo::TextExtents txext;
	cairoctx->get_text_extents( text, txext );

	// 描画(センタリング)
	cairoctx->move_to( width/2 - txext.width/2 - txext.x_bearing, y - txext.y_bearing );
	cairoctx->show_text( text );
	
	// 次の文字列のy座標
	y += txext.height + 10;
	
	str = "かきくけこ";
	text = Glib::locale_to_utf8(str);

	// フォント指定
	std::string fontName = "Monospace";
	Glib::ustring uFontName = Glib::locale_to_utf8(fontName);
	cairoctx->select_font_face( uFontName, Cairo::FONT_SLANT_NORMAL, Cairo::FONT_WEIGHT_NORMAL );
	cairoctx->set_font_size( 24 * resolution / 72 );
    
	// 色指定
	Gdk::Cairo::set_source_color( cairoctx, Gdk::Color( "red" ) ); 

	// extents取得
	cairoctx->get_text_extents( text, txext );

	// 描画(センタリング)
	cairoctx->move_to( width/2 - txext.width/2 - txext.x_bearing, y - txext.y_bearing );
	cairoctx->show_text( text );

	return true;
}
class MainWin : public Gtk::Window
{
    MyDrawArea m_drawarea;
public:
    MainWin(){
        add( m_drawarea );
        show_all_children();
    }
};
int main( int argc, char *argv[] )
{
    Gtk::Main kit( argc, argv );
    MainWin mainwin;
    Gtk::Main::run( mainwin );

    return 0;
}