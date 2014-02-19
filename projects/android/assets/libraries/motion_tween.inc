/* ISSUES * 

- Data types (How we know what type of value we need to set to the argument property?).
- Kill all running process (How we can kill the effects?).

*/

import "mod_say";
import "mod_map"
import "mod_key"
import "mod_grproc"
import "mod_proc"
import "mod_video"
import "mod_math"

Const
	ALPHA_GRADE = 1.70158;
	BETA_GRADE = 1.525;
End


Global
	struct motion_effect
		// Regular
		int regularEaseIn = 1;
		int regularEaseOut = 2;
		int regularEaseInOut = 3;
		// Bounce
		int bounceEaseIn = 4;
		int bounceEaseOut = 5;
		int bounceEaseInOut = 6;
		// Back
		int backEaseIn = 7;
		int backEaseOut = 8;
		int backEaseInOut = 9;
		// Strong
		int strongEaseIn = 10;
		int strongEaseOut = 11;
		int strongEaseInOut = 12;
		//Elastic
		int elasticEaseIn = 13;
		int elasticEaseOut = 14;
		int elasticEaseInOut = 15;    	
	end
End


Type type_effect
	int* property;
	int  effectType;
	int  fromValue;
	int  toValue;
	int  duration;
	int  start;
End

//Back
Function int backEaseIn(float _step, int _initial_value, int _nro_steps, int _duration);
Private
	float s;
Begin
 	s = ALPHA_GRADE;
	return _nro_steps*(_step/=_duration)*_step*((s+1)*_step - s) + _initial_value;
End
Function int backEaseOut(float _step, int _initial_value, int _nro_steps, int _duration);
Private
	float s;
Begin
	s = ALPHA_GRADE;
	return _nro_steps*((_step/=_duration-1)*_step*((s+1)*_step + s) + 1) + _initial_value;
End
Function int backEaseInOut(float _step, int _initial_value, int _nro_steps, int _duration);
Private
	float s;
	float resultado;
Begin
	s = ALPHA_GRADE;
	if ((_step/=_duration/2) < 1) 
		resultado = _nro_steps/2*(_step*_step*(((s*=(BETA_GRADE))+1)*_step - s)) + _initial_value;
	else
		resultado = _nro_steps/2*((_step-=2)*_step*(((s*=(BETA_GRADE))+1)*_step + s) + 2) + _initial_value;
	end
	return resultado;
End

//Strong
Function int strongEaseIn(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	return _nro_steps*(_step/=_duration)* _step*_step*_step*_step + _initial_value;
End
Function int strongEaseOut(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	return _nro_steps*((_step/=_duration-1)*_step*_step*_step*_step + 1) + _initial_value;
End
Function int strongEaseInOut(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	if ((_step/=_duration/2) < 1) 
		return _nro_steps/2*_step*_step*_step*_step*_step + _initial_value;
	end
	return _nro_steps/2*((_step-=2)*_step*_step*_step*_step + 2) + _initial_value;
End

//Bounce
Function int bounceEaseOut(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	if ((_step/=_duration) < (1/2.75)) 
		return _nro_steps*(7.5625*_step*_step) + _initial_value;
	elseif (_step < (2/2.75)) 
		return _nro_steps*(7.5625*(_step-=(1.5/2.75))*_step + 0.75) + _initial_value;
	elseif (_step < (2.5/2.75)) 
		return _nro_steps*(7.5625*(_step-=(2.25/2.75))*_step + 0.9375) + _initial_value;
	else 
		return _nro_steps*(7.5625*(_step-=(2.625/2.75))*_step + 0.984375) + _initial_value;
	end
End
Function int bounceEaseIn(float _step, int _initial_value, int _nro_steps, int _duration);
begin
	return _nro_steps - bounceEaseOut (_duration-_step, 0, _nro_steps, _duration) + _initial_value;
end
Function int bounceEaseInOut(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	if (_step < _duration/2) 
		return bounceEaseIn (_step*2, 0, _nro_steps, _duration) * 0.5 + _initial_value;
	else 
		return bounceEaseOut (_step*2-_duration, 0, _nro_steps, _duration) * 0.5 + _nro_steps*0.5 + _initial_value;
	end
End

// Regular
Function float regularEaseIn(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	return _nro_steps*(_step/=_duration)*_step + _initial_value;	
End

Function float regularEaseOut(float _step, int _initial_value, int _nro_steps, int _duration);
private
	float result;
Begin
	result = (-_nro_steps*(_step/=_duration)*(_step-2) + _initial_value);
	/*say(_step);
	say(_initial_value);
	say(_nro_steps);
	say(_duration);
	say(result);*/
	return result;
End

Function float regularEaseInOut(float _step, int _initial_value, int _nro_steps, int _duration);
Begin
	if ((_step/=_duration/2) < 1) 
		return _nro_steps/2*_step*_step + _initial_value;
	end
	return -_nro_steps/2 * ((--_step)*(_step-2) - 1) + _initial_value;
end

//Elastic
Function int elasticEaseIn(float _step, int _initial_value, int _nro_steps, int _duration);
private
	float a;
	float p;
	float s;
Begin
		if (_step==0) 
			return _initial_value;
		end
		if ((_step/=_duration)==1) 
			return _initial_value+_nro_steps;
		end
		p=_duration*0.3;
		if (a < abs(_nro_steps)) 
			a=_nro_steps; 
			s=p/4;
		else 
			s = p/(2*PI) * asin (_nro_steps/a);
		end
		
		return -(a*pow(2,10*(_step-=1)) *sin( (_step*_duration-s)*(2*PI)/p )) + _initial_value;
End
Function int elasticEaseOut(float _step, int _initial_value, int _nro_steps, int _duration);
private
	float a;
	float p;
	float s;
Begin
	if (_step==0) 
		return _initial_value;
	end
	if ((_step/=_duration)==1)
		return _initial_value+_nro_steps;
	end
	p=_duration*0.3;
	if (a < abs(_nro_steps))
		a=_nro_steps;
		s=p/4;
	else
		s = p/(2*PI) * asin (_nro_steps/a);
	end
	return (a*pow(2,-10*_step) * sin( (_step*_duration-s)*(2*PI)/p ) + _nro_steps + _initial_value);
End
Function int elasticEaseInOut(float _step, int _initial_value, int _nro_steps, int _duration);
private
	float a;
	float p;
	float s;
Begin
	if (_step==0)
		return _initial_value;
	end
	if ((_step/=_duration/2)==2)
		return _initial_value+_nro_steps;
	end
	p=_duration*(0.3*1.5);
	if (a < abs(_nro_steps))
		a=_nro_steps;
		s=p/4;
	else
		s = p/(2*PI) * asin (_nro_steps/a);
	end
	if (_step < 1)
		return -0.5*(a*pow(2,10*(_step-=1)) * sin( (_step*_duration-s)*(2*PI)/p )) + _initial_value;
	end
	return a*pow(2,-10*(_step-=1)) * sin( (_step*_duration-s)*(2*PI)/p )*0.5 + _nro_steps + _initial_value;
End


Function float _callEffectFunction(float _step, int _initial_value, int _nro_steps, int _duration, int effect);
Begin
	switch(effect)
		// Regular
		case motion_effect.regularEaseIn:
			return regularEaseIn(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.regularEaseOut:
			return regularEaseOut(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.regularEaseInOut:
			return regularEaseInOut(_step, _initial_value, _nro_steps, _duration);
		end
		// Bounce
		case motion_effect.bounceEaseIn:
			return bounceEaseIn(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.bounceEaseOut:
			return bounceEaseOut(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.bounceEaseInOut:
			return bounceEaseInOut(_step, _initial_value, _nro_steps, _duration);
		end
		// Back
		case motion_effect.backEaseIn:
			return backEaseIn(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.backEaseOut:
			return backEaseOut(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.backEaseInOut:
			return backEaseInOut(_step, _initial_value, _nro_steps, _duration);
		end
		// Strong
		case motion_effect.strongEaseIn:
			return strongEaseIn(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.strongEaseOut:
			return strongEaseOut(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.strongEaseInOut:
			return strongEaseInOut(_step, _initial_value, _nro_steps, _duration);
		end
		//Elastic
		case motion_effect.elasticEaseIn:
			return elasticEaseIn(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.elasticEaseOut:
			return elasticEaseOut(_step, _initial_value, _nro_steps, _duration);
		end
		case motion_effect.elasticEaseInOut:
			return elasticEaseInOut(_step, _initial_value, _nro_steps, _duration);
		end
	end
End

function int calculateSteps(type_effect _effects, int _nro_effects);
private
	int i;
	type_effect temp_effect;
	int nro_frames;
	int max_frames = -1;
Begin
	for(i=0;i<_nro_effects;i++)
		temp_effect = _effects[i];
		nro_frames = temp_effect.duration + temp_effect.start;
		if(nro_frames>max_frames)
			max_frames=nro_frames;
		End
	end
	return max_frames;
End

function fixInitialValue(type_effect _effects, int _nro_effects);
private
	int i;
begin
	For(i=0;i<_nro_effects;i++)
		*_effects[i].property = _effects[i].fromValue;
	end
end

process applyMultiEffects(type_effect _effects, int _nro_effects);
private
	int _total_duration;
	int i;
	int j;
	float _value;
begin
	_total_duration = calculateSteps(_effects,_nro_effects);
	For(i=0;i<_total_duration;i++)
		For(j=0;j<_nro_effects;j++)
			if(i>=_effects[j].start && _effects[j].duration>=(i-_effects[j].start))
				_value = _callEffectFunction(i-_effects[j].start, _effects[j].fromValue, (_effects[j].toValue - _effects[j].fromValue),_effects[j].duration,_effects[j].effectType);
				//say(_value);
				*_effects[j].property = _value;
			End
		End
		frame;
	End
	frame;
end

/**
	* This function aply an effect to the argument property (not sincronized efect - all at the same time) 
	*
	* @param propiedad: It is modified by the fuction with the selected effect
	* @param effecto:	define the effect to apply
	* @param valorFinal: define the final value that the property will have when the effect finish.
	* @param duracion: define the time duration of the effect (in frames).
*/
Process applyEffect(type_effect _effect);
Private
	int _nro_steps;
	float _step;
	float _value;
Begin
	_nro_steps = _effect.toValue - _effect.fromValue;
	_step = 0;
	Repeat
		_value = _callEffectFunction(_step, _effect.fromValue, _nro_steps, _effect.duration, _effect.effectType);
		//say(_value);
		*_effect.property = _value;//_callEffectFunction(_step, _effect.fromValue, _nro_steps, _effect.duration, _effect.effectType);
		_step++;
		frame;
	Until(_step==(_effect.duration+1))
	frame;
End