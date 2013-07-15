#include <mruby.h>
#include <mruby/string.h>
#include <mruby/value.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/variable.h>
#include <stdio.h>
#include <unistd.h>

#include <directfb.h>

#include "directfb_descriptions.h"

// ============================================================================
// IDirectFB::Result object - DFBResult

struct mrb_directfb_input_device_description_data {
    DFBInputDeviceDescription input_device_description;
};

static void mrb_directfb_input_device_description_free(mrb_state* mrb, void* p)
{
    struct mrb_directfb_input_device_description_data* data = (struct mrb_directfb_input_device_description_data*)p;
    if (data != NULL) {
        mrb_free(mrb, p);
    }
}

static struct mrb_data_type mrb_directfb_input_device_description_type = {"InputDeviceDescription", mrb_directfb_input_device_description_free};

mrb_value mrb_directfb_input_device_description_wrap(mrb_state* mrb, struct RClass* c, DFBInputDeviceDescription* desc)
{
    struct mrb_directfb_input_device_description_data* data = 
        (struct mrb_directfb_input_device_description_data*)mrb_malloc(mrb, sizeof(struct mrb_directfb_input_device_description_data));
    if (data == NULL) {
        return mrb_nil_value();
    }

    if (desc != NULL) {
        memcpy(&data->input_device_description, desc, sizeof(data->input_device_description));
    } else {
        memset(&data->input_device_description, 0, sizeof(data->input_device_description));
    }

    return mrb_obj_value(Data_Wrap_Struct(mrb, c, &mrb_directfb_input_device_description_type, data));
}

DFBInputDeviceDescription* mrb_directfb_input_device_description_get(mrb_state *mrb, mrb_value value)
{
    struct mrb_directfb_input_device_description_data* data = 
        (struct mrb_directfb_input_device_description_data*)mrb_data_get_ptr(mrb, value, &mrb_directfb_input_device_description_type);
    return (data != NULL)? &data->input_device_description : NULL;
}

static mrb_value input_device_description_new(mrb_state *mrb, mrb_value self)
{
    return mrb_directfb_input_device_description_wrap(mrb, mrb_class_ptr(self), NULL);
}

static mrb_value input_device_description_type(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->type);
}

static mrb_value input_device_description_caps(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->caps);
}

static mrb_value input_device_description_min_keycode(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->min_keycode);
}

static mrb_value input_device_description_max_keycode(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->max_keycode);
}

static mrb_value input_device_description_max_axis(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->max_axis);
}

static mrb_value input_device_description_max_button(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_fixnum_value(desc->max_button);
}

static mrb_value input_device_description_name(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_str_new(mrb, desc->name, DFB_INPUT_DEVICE_DESC_NAME_LENGTH);
}

static mrb_value input_device_description_vendor(mrb_state *mrb, mrb_value self)
{
    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    return mrb_str_new(mrb, desc->vendor, DFB_INPUT_DEVICE_DESC_VENDOR_LENGTH);
}

static mrb_value input_device_description_to_s(mrb_state *mrb, mrb_value self)
{
    char s[512];
    s[511] = '\0';

    DFBInputDeviceDescription* desc = mrb_directfb_input_device_description_get(mrb, self);
    if (desc == NULL) {
        return mrb_nil_value();
    }

    snprintf(s, sizeof(s)-1, "type:%d, caps:0x%08x, min_keycode:%d, max_keycode:%d, max_axis:%d, max_button:%d"
            , desc->type, desc->caps, desc->min_keycode, desc->max_keycode, desc->max_axis, desc->max_button);

    return mrb_str_new(mrb, desc->vendor, DFB_INPUT_DEVICE_DESC_VENDOR_LENGTH);
}

static void define_input_device_description(mrb_state* mrb, struct RClass* outer)
{
    struct RClass* cls = mrb_define_class_under(mrb, outer, "InputDeviceDescription", mrb->object_class);
    mrb_define_class_method(mrb, cls, "new", input_device_description_new, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "type", input_device_description_type, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "caps", input_device_description_caps, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "min_keycode", input_device_description_min_keycode, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "max_keycode", input_device_description_max_keycode, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "max_axis", input_device_description_max_axis, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "max_button", input_device_description_max_button, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "name", input_device_description_name, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "vendor", input_device_description_vendor, MRB_ARGS_NONE());
    mrb_define_method(mrb, cls, "to_s", input_device_description_to_s, MRB_ARGS_NONE());
}





void mrb_directfb_define_descriptions(mrb_state* mrb, struct RClass* outer)
{
    define_input_device_description(mrb, outer);
}

