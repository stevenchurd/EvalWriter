var stack = []

function push(element)
{
    if(stack.length > 0)
    {
        stack[stack.length-1].parent = null
    }

    stack.push(element)
}

function pop()
{
    var element = stack.pop()
    return element
}



function top()
{
    return stack[stack.length-1]
}
