#include "coordinate_translator.h"

Coordinate_translator::Coordinate_translator()
{

}

Coordinate_translator::Coordinate_translator(graph_info* info)
{
    _info = info;
}

// convert cartesian to screen coor
sf::Vector2f Coordinate_translator::translate(sf::Vector2f point) 
{
	/*
	screenX = cartX * zoom_factor + screen_width/2 + offsetX
	screenY = -cartY * zoom_factor + screen_height/2  + offsetY
	*/

	_info->_scale.x = _info->_window_dimension.x / (_info->_domain.y - _info->_domain.x);;
	_info->_scale.y = _info->_window_dimension.y / (_info->_range.y - _info->_range.x);;

	double x = point.x * _info->_scale.x + (_info->_origin.x + _info->_offset.x);
	double y = -point.y * _info->_scale.y + (_info->_origin.y + _info->_offset.y);

    return sf::Vector2f(x,y);
}

sf::Vector2f Coordinate_translator::operator()(sf::Vector2f point)
{
    return translate(point);
}
