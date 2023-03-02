#include "system.h"

System::System()
{

}

System::System(graph_info* info)
{
    _g.set_info(info);
    _info = info;
}

void System::set_info(graph_info* info)
{
    _g.set_info(info);
    _info = info;    
}

void System::Step(int command, graph_info* info)
{
    // [TODO] Fix zoom scaling independent of origin

    // cout << _info->_window_dimension.x << " and " << _info->_window_dimension.y << endl;
    // cout << _info->_origin.x << " and " << _info->_origin.y << endl;
    // cout << _info->_domain.x << " and " << _info->_domain.y << endl;
    // cout << _info->_range.x << " and " << _info->_range.y << endl;
    // cout << _info->_scale.x << " and " << _info->_scale.y << endl;


    // double midx = (_info->_domain.y + _info->_domain.x) / 2;
    // double midy = (_info->_range.y + _info->_range.x) / 2;
    // double ldist = abs(midx - _info->_domain.x);
    // double rdist = abs(midx - _info->_domain.y);
    // double udist = abs(midy - _info->_range.x);
    // double ddist = abs(midy - _info->_range.y);

    // cout << "mid: (" <<midx << "," << midy << ") ,"
    //         << "hdist: (" << ldist << "," << rdist  << ")" 
    //         << "vdist: (" << udist << "," << ddist  << ")"<< endl;

    // cout << "domain: (" <<_info->_domain.x << "," << _info->_domain.y << "), " 
    //     << "range: (" <<_info->_range.x << "," << _info->_range.y << "), "
    //     << "origin: (" <<_info->_origin.x << "," << _info->_origin.y << "), "  
    //     << "scale: (" <<_info->_scale.x << "," << _info->_scale.y << "), "  
    //     << "offset: (" << _info->_offset.x << "," << _info->_offset.y << "), "  
    //     << endl;

    double zoom_factor = 1.1;

	switch (command) {
	case UP:
        // _info->_origin.y += _info->_scale.y;
        _info->_offset.y += _info->_scale.y;
        _info->_range.x += 1;
        _info->_range.y += 1;
		break;

	case DOWN:
        // _info->_origin.y -= _info->_scale.y;
        _info->_offset.y -= _info->_scale.y;
        _info->_range.x -= 1;
        _info->_range.y -= 1;
		break;	
        
    case LEFT:
        // _info->_origin.x += _info->_scale.x;
        _info->_offset.x += _info->_scale.x;
        _info->_domain.x -= 1;
        _info->_domain.y -= 1;
		break;

	case RIGHT:
        // _info->_origin.x -= _info->_scale.x;
        _info->_offset.x -= _info->_scale.x;
        _info->_domain.x += 1;
        _info->_domain.y += 1;
		break;
    
	case ZOOMOUT:

        if(_info->_showGrid && _info->_scale.x > 75)
        {
            _info->_scale.x /= 2;
            _info->_scale.y /= 2;

            _info->_domain.x *= 2;
            _info->_domain.y *= 2;
            _info->_range.x *= 2;
            _info->_range.y *= 2;
        }

        if(!_info->_showGrid)
        {
            // scroll down zoom out
            _info->_scale.x /= zoom_factor;
            _info->_scale.y /= zoom_factor;

            _info->_domain.x *= zoom_factor;
            _info->_domain.y *= zoom_factor;
            _info->_range.x *= zoom_factor;
            _info->_range.y *= zoom_factor;

            if(_info->_offset.x  < 0){
                //left
                _info->_offset.x += _info->_scale.x;
                _info->_domain.x -= 1;
                _info->_domain.y -= 1;
            }
            else if(_info->_offset.x > 0){
                //right
                _info->_offset.x -= _info->_scale.x;
                _info->_domain.x += 1;
                _info->_domain.y += 1;
            }  
        }
		break;

	case ZOOMIN:
        
        if(_info->_showGrid && _info->_scale.x < 300)
        {
            _info->_scale.x *= 2;
            _info->_scale.y *= 2;

            _info->_domain.x /= 2;
            _info->_domain.y /= 2;
            _info->_range.x /= 2;
            _info->_range.y /= 2;
        }

        if(!_info->_showGrid)
        {
            // scroll up zoom in
            _info->_scale.x *= zoom_factor;
            _info->_scale.y *= zoom_factor;

            _info->_domain.x /= zoom_factor;
            _info->_domain.y /= zoom_factor;
            _info->_range.x /= zoom_factor;
            _info->_range.y /= zoom_factor;
    

            if(_info->_offset.x  < 0){       // pos x-axis
                //right
                _info->_offset.x -= _info->_scale.x;
                _info->_domain.x += 1;
                _info->_domain.y += 1;
            }
            else if(_info->_offset.x > 0){   // neg x-axis
                //left
                _info->_offset.x += _info->_scale.x;
                _info->_domain.x -= 1;
                _info->_domain.y -= 1;
            }
        }
		break;

	case RESET:
        _info->_origin = sf::Vector2f(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
		_info->_offset = sf::Vector2f(0, 0);
		_info->_domain = sf::Vector2f(-8, 8);
		_info->_range = sf::Vector2f(-8, 8);
        _info->_scale = sf::Vector2f(_info->_window_dimension.x / (_info->_domain.y - _info->_domain.x),
                                    _info->_window_dimension.y / (_info->_range.y - _info->_range.x));
		break;

    case TAB:
        if(_info->_tab)
            _info->_tab = false;
        else  
            _info->_tab = true;
        break;

    case COOR:
        if(_info->_showCoor)
            _info->_showCoor = false;
        else  
            _info->_showCoor = true;
        break;

    case GRID:
        if(_info->_showGrid)
            _info->_showGrid = false;
        else  
            _info->_showGrid = true;
        break;
	}
    _g.update(info);
}

void System::Draw(sf::RenderWindow &window)
{
    _g.draw(window);
}
